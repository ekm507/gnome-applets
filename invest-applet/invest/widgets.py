import os, time
from os.path import *
import gnomeapplet, gtk, gtk.gdk, gconf, gobject, pango
from gettext import gettext as _
import gtk, gtk.glade, egg.trayicon, gobject, gnomevfs
import csv, os
from gettext import gettext as _
import invest, invest.about, invest.chart
from invest.quotes import get_quotes_updater
from invest import *

COLORSCALE_POSITIVE = [
	"white",
	"#ad7fa8",
	"#75507b",
	"#5c3566",
	"#729fcf",
	"#3465a4",
	"#204a87",
	"#8ae234",
	"#73d216",
	"#4e9a06",
]
GREEN = COLORSCALE_POSITIVE[-1]
COLORSCALE_NEGATIVE = [
	"white",
	"#fce94f",
	"#e9b96e",
	"#fcaf3e",
	"#c17d11",
	"#f57900",
	"#ce5c00",
	"#ef2929",
	"#cc0000",
	"#a40000",
]
RED = COLORSCALE_NEGATIVE[-1]

class InvestWidget(gtk.TreeView):
	def __init__(self):
		gtk.TreeView.__init__(self)
				
		self.set_property("headers-visible", False)
		self.set_property("rules-hint", True)
		self.set_reorderable(True)
		
		cell = gtk.CellRendererText ()
		self.column_description = gtk.TreeViewColumn ("Description", cell)
		self.column_description.set_cell_data_func(cell, self._get_cell_data)
		
		self.append_column(self.column_description)
		self.connect('row-activated', self.on_row_activated)
		
		self.set_model(get_quotes_updater())
	
	def _get_cell_data(self, column, cell, model, iter):
		color = GREEN
		if model[iter][model.BALANCE] < 0:
			color = RED
						
		cell.set_property('markup',
			"<span face='Monospace'>%s: <span foreground='%s'>%+.2f</span> (<span foreground='%s'>%+.2f%%</span>) %.2f</span>" %
			(model[iter][model.SYMBOL], color, model[iter][model.BALANCE], color, model[iter][model.BALANCE_PCT], model[iter][model.VALUE]))
				
	def on_row_activated(self, treeview, path, view_column):
		ticker = self.get_model()[self.get_model().get_iter(path)][0]
		if ticker == None:
			return
		
		invest.chart.show_chart([ticker])

gobject.type_register(InvestWidget)
	
class InvestTicker(gtk.Label):
	def __init__(self):
		gtk.Label.__init__(self, _("Waiting..."))
		
		self.quotes = []
		gobject.timeout_add(TICKER_TIMEOUT, self.scroll_quotes)
		
		get_quotes_updater().connect('quotes-updated', self.on_quotes_update)
						
	def on_quotes_update(self, updater):
		self.quotes = []
		updater.foreach(self.update_quote, None)
	
	def update_quote(self, model, path, iter, user_data):
		color = GREEN
		if model[iter][model.BALANCE] < 0:
			color = RED
		
		self.quotes.append(
			"%s: <span foreground='%s'>%+.2f (%+.2f%%)</span> %.2f" %
			(model[iter][model.SYMBOL], color, model[iter][model.BALANCE], model[iter][model.BALANCE_PCT], model[iter][model.VALUE]))
				
	def scroll_quotes(self):
		if len(self.quotes) == 0:
			return True
		
		q = self.quotes.pop()
		self.set_markup("<span face='Monospace'>%s</span>" % q)
		self.quotes.insert(0, q)
		
		return True

gobject.type_register(InvestTicker)

class InvestTrend(gtk.Image):	
	def __init__(self):
		gtk.Image.__init__(self)
		self.pixbuf = None
		self.previous_allocation = (0,0)
		self.connect('size-allocate', self.on_size_allocate)
		get_quotes_updater().connect('quotes-updated', self.on_quotes_update)
	
	def on_size_allocate(self, widget, allocation):
		if self.previous_allocation == (allocation.width, allocation.height):
			return
			
		self.pixbuf = gtk.gdk.Pixbuf(gtk.gdk.COLORSPACE_RGB, True, 8, allocation.height, allocation.height)
		self.set_color("grey")
		self.previous_allocation = (allocation.width, allocation.height)
		
	def set_color(self, color, opacity=0xFF):
		if self.pixbuf != None:
			try:
				color = pango.Color(color)
				factor = float(0xFF)/0xFFFF
				self.pixbuf.fill(
					int(color.red*factor)<<24|int(color.green*factor)<<16|int(color.blue*factor)<<8|opacity)
				self.set_from_pixbuf(self.pixbuf)
			except Exception, e:
				print e

	def on_quotes_update(self, updater):
		start_total = 0
		now_total = 0
		for row in updater:
			var = row[updater.VARIATION]/100
			now = row[updater.VALUE]

			start = now / (1 + var)
			
			portfolio_number = sum([purchase["amount"] for purchase in invest.STOCKS[row[updater.SYMBOL]]])
			start_total += start * portfolio_number
			now_total += now * portfolio_number
		
		day_var = (now_total - start_total) / start_total * 100
		color = int(2*day_var)
		opacity = min(0xFF, int(abs(127.5*day_var)))
		if day_var < 0:
			color = COLORSCALE_NEGATIVE[min(len(COLORSCALE_NEGATIVE)-1, abs(color))]
		else:
			color = COLORSCALE_POSITIVE[min(len(COLORSCALE_POSITIVE)-1, abs(color))]

		self.set_color(color, opacity)
	
gobject.type_register(InvestTrend)