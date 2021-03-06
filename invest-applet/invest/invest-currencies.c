/*
 * Copyright (C) 2004-2005 Raphael Slinckx
 * Copyright (C) 2009-2011 Enrico Minack
 * Copyright (C) 2016 Alberts Muktupāvels
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *     Alberts Muktupāvels <alberts.muktupavels@gmail.com>
 *     Enrico Minack <enrico-minack@gmx.de>
 *     Raphael Slinckx <raphael@slinckx.net>
 */

#include "config.h"
#include "invest-currencies.h"

const InvestCurrencies currencies[] =
  {
    { "BZD", "Belize Dollar" },
    { "NLG", "Dutch Guilder" },
    { "SLL", "Sierra Leone Leone" },
    { "FRF", "French Franc" },
    { "NGN", "Nigerian Naira" },
    { "CRC", "Costa Rican Colon" },
    { "LAK", "Laos Kip" },
    { "CLP", "Chilean Peso" },
    { "DZD", "Algerian Dinar" },
    { "SZL", "Swaziland Lilangeni" },
    { "MUR", "Mauritius Rupee" },
    { "WST", "Western Samoa Tala" },
    { "MMK", "Myanmar Kyat" },
    { "IDR", "Indonesian Rupiah" },
    { "GTQ", "Guatemala Quetzal" },
    { "CAD", "Canadian Dollar" },
    { "AWG", "Aruban Florin" },
    { "TTD", "Trinidad Dollar" },
    { "PKR", "Pakistani Rupee" },
    { "XCD", "East Caribbean Dollar" },
    { "VUV", "Vanuatu Vatu" },
    { "XOF", "CFA Franc (BCEAO)" },
    { "ROL", "Romanian Leu" },
    { "KMF", "Comoros Franc" },
    { "SIT", "Slovenian Tolar" },
    { "VEB", "Venezuelan Bolivar" },
    { "ANG", "Netherlands Antilles Guilder" },
    { "MNT", "Mongolian Tugrik" },
    { "LBP", "Lebanese Pound" },
    { "KES", "Kenyan Shilling" },
    { "BTN", "Bhutan Ngultrum" },
    { "GBP", "British Pound" },
    { "SEK", "Swedish Krona" },
    { "ZMK", "Zambia Kwacha" },
    { "SKK", "Slovak Koruna" },
    { "DKK", "Danish Krone" },
    { "AFA", "Afganistan Afghani" },
    { "CYP", "Cypriot Pound" },
    { "SCR", "Seychelles Rupee" },
    { "FJD", "Fiji Dollar" },
    { "SRG", "Surinam Guilder" },
    { "SHP", "St. Helena Pound" },
    { "ALL", "Albanian Lek" },
    { "TOP", "Tonga Isl Pa'anga" },
    { "UGX", "Ugandan Shilling" },
    { "OMR", "Oman Rial" },
    { "DJF", "Djibouti Franc" },
    { "BND", "Brunei Dollar" },
    { "TND", "Tunisian Dinar" },
    { "PTE", "Portuguese Escudo" },
    { "IEP", "Irish Punt" },
    { "SBD", "Salomon Islands Dollar" },
    { "GNF", "Guinea Franc" },
    { "BOB", "Bolivian Boliviano" },
    { "CVE", "Cape Verde Escudo" },
    { "ARS", "Argentinian Peso" },
    { "GMD", "Gambia Dalasi" },
    { "ZWD", "Zimbabwean Dollar" },
    { "MWK", "Malawi Kwacha" },
    { "BDT", "Bangladesh Taka" },
    { "GRD", "Greek Drachma" },
    { "KWD", "Kuwaiti Dinar" },
    { "EUR", "Euro" },
    { "TRL", "Turkish Lira" },
    { "CHF", "Swiss Franc" },
    { "DOP", "Dominican Peso" },
    { "PEN", "Peruvian Sol" },
    { "SVC", "El Salvador Colon" },
    { "SGD", "Singapore Dollar" },
    { "TWD", "Taiwan New Dollar" },
    { "USD", "US Dollar" },
    { "BGN", "Bulgarian Lev" },
    { "MAD", "Moroccan Dirham" },
    { "SAR", "Saudi Arabian Riyal" },
    { "AUD", "Australian Dollar" },
    { "KYD", "Cayman Islands Dollar" },
    { "GHC", "Ghanaian Cedi" },
    { "KRW", "South Korean Won" },
    { "GIP", "Gibraltar Pound" },
    { "NAD", "Namibian Dollar" },
    { "CZK", "Czech Koruna" },
    { "JMD", "Jamaican Dollar" },
    { "MXN", "Mexican Peso" },
    { "BWP", "Botswana Pula" },
    { "GYD", "Guyana Dollar" },
    { "EGP", "Egyptian Pound" },
    { "THB", "Thai Baht" },
    { "AED", "United Arab Emirates Dirham" },
    { "JPY", "Japanese Yen" },
    { "JOD", "Jordanian Dinar" },
    { "HRK", "Croatian Kuna" },
    { "ZAR", "South African Rand" },
    { "CUP", "Cuban Peso" },
    { "BBD", "Barbados Dollar" },
    { "PGK", "Papua New Guinea Kina" },
    { "LKR", "Sri Lanka Rupee" },
    { "BEF", "Belgian Franc" },
    { "PLN", "Polish Zloty" },
    { "MYR", "Malaysian Ringgit" },
    { "FIM", "Finnish Markka" },
    { "CNY", "Renmimbi Yuan" },
    { "SDD", "Sudanese Dinar" },
    { "LVL", "Latvian Lats" },
    { "ITL", "Italian Lira" },
    { "INR", "Indian Rupee" },
    { "NIO", "Nicaraguan Cordoba" },
    { "PHP", "Philippines Peso" },
    { "HNL", "Honduras Lempira" },
    { "HKD", "Hong Kong Dollar" },
    { "NZD", "New Zealand Dollar" },
    { "BRL", "Brazilian Real" },
    { "MTL", "Maltese Pound" },
    { "ATS", "Austrian Schilling" },
    { "EEK", "Estonian Kroon" },
    { "NOK", "Norwegian Krone" },
    { "ISK", "Iceland Krona" },
    { "ILS", "Israeli Shekel" },
    { "LSL", "Lesotho Loti" },
    { "HUF", "Hungarian Forint" },
    { "ESP", "Spanish Peseta" },
    { "UAH", "Ukraine Hryvnia" },
    { "RUB", "Russian Ruble" },
    { "BMD", "Bermuda Dollar" },
    { "MVR", "Maldives Rufiyan" },
    { "QAR", "Qatari Rial" },
    { "VND", "Vietnam Dong" },
    { "MRO", "Mauritania Ouguiya" },
    { "MZM", "Mozambique Metical" },
    { "NPR", "Nepal Rupee" },
    { "COP", "Colombian Peso" },
    { "TZS", "Tanzanian Shilling" },
    { "MGF", "Malagasy Franc" },
    { "KHR", "Cambodian Riel" },
    { "SYP", "Syria Pound" },
    { "HTG", "Haitian Gourde" },
    { "DEM", "German Mark" },
    { "BHD", "Bahraini Dinar" },
    { "XAF", "CFA Franc(BEAC)" },
    { "STD", "Sao Tome & Principe Dobra" },
    { "LTL", "Lithuanian Litas" },
    { "ETB", "Ethiopian Birr" },
    { "XPF", "CFP Franc" },
    { NULL, NULL }
  };

gboolean
invest_currencies_contains (const gchar *currency)
{
  guint i;

  if (currency == NULL)
    return FALSE;

  for (i = 0; currencies[i].code != NULL; i++)
    {
      if (g_strcmp0 (currencies[i].code, currency) == 0)
        return TRUE;
    }

  return FALSE;
}
