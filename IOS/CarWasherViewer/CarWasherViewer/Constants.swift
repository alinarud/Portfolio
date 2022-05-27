//
//  Constants.swift
//  DeWash
//
//  Created by user on 11.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import Foundation
import UIKit

struct Constants {
    static let YEAR_MONTHS  = 12
    static let MONTH_DAYS   = 31
    static let DAY_HOURS    = 24
    static let UPDATE_TIMER = 30
    
    struct ChartFilter {
        static let chemistry_consumption   	= 0
        static let electricity_consumption 	= 1
        static let water_consumption 		= 2
        static let spent_money 				= 3
        static let working_time 			= 4
    }
    
    struct Modes {
        static let MODE_1   = 1
        static let MODE_2   = 2
        static let MODE_3   = 3
        static let MODE_4   = 4
        static let MODE_5   = 5
        static let MODE_6   = 6
        static let MODE_7   = 7
        static let MODE_8   = 8
        static let MODE_9   = 9
        static let MODE_10  = 10
        static let MODE_11  = 11
        static let MODE_12  = 12
        static let MODE_13  = 13
    }
    
    struct Colors {
        static let light_blue = UIColor(red: 220/255.0, green: 236/255.0, blue: 255/255.0, alpha: 1)
        
        static let water_presure    = UIColor( red: 0/255.0, green: 84/255.0, blue: 147/255.0, alpha: 1) //0xff0000ff
        static let vacuum_cleaner   = UIColor( red: 0/255.0, green: 250/255.0, blue: 146/255.0, alpha: 1) //0xff32cd32
        static let disk_clean       = UIColor( red: 148/255.0, green: 82/255.0, blue: 0/255.0, alpha: 1) //0xffa0522d
        static let foam             = UIColor( red: 0/255.0, green: 150/255.0, blue: 255/255.0, alpha: 1) //0xff87ceeb
        static let hand_water       = UIColor( red: 148/255.0, green: 17/255.0, blue: 0/255.0, alpha: 1) //0xffff0000
        static let winter           = UIColor( red: 214/255.0, green: 214/255.0, blue: 214/255.0, alpha: 1) //0xffdeb887
        static let vax              = UIColor( red: 255/255.0, green: 147/255.0, blue: 0/255.0, alpha: 1) //0xffff7f50
        static let air              = UIColor( red: 255/255.0, green: 126/255.0, blue: 121/255.0, alpha: 1) //0xffffdab9
        static let carpet_clean     = UIColor( red: 146/255.0, green: 144/255.0, blue: 0/255.0, alpha: 1) //0xffff69b4
        static let osmosis          = UIColor( red: 255/255.0, green: 212/255.0, blue: 121/255.0, alpha: 1) //0xffffa500
        static let tire             = UIColor( red: 148/255.0, green: 55/255.0, blue: 255/255.0, alpha: 1) //0xff6a5acd
        static let warm_water       = UIColor( red: 0/255.0, green: 144/255.0, blue: 81/255.0, alpha: 1)  //0xff008000
        static let antimoshka       = UIColor( red: 215/255.0, green: 131/255.0, blue: 255/255.0, alpha: 1) //0xffdda0dd
        
        static let exp_color1 = UIColor( red: 0/255.0, green: 84/255.0, blue: 147/255.0, alpha: 1)
        static let exp_color2 = UIColor( red: 0/255.0, green: 250/255.0, blue: 146/255.0, alpha: 1)
        static let exp_color3 = UIColor( red: 148/255.0, green: 82/255.0, blue: 0/255.0, alpha: 1)
        static let exp_color4 = UIColor( red: 0/255.0, green: 150/255.0, blue: 255/255.0, alpha: 1)
        static let exp_color5 = UIColor( red: 148/255.0, green: 17/255.0, blue: 0/255.0, alpha: 1)
        static let exp_color6 = UIColor( red: 214/255.0, green: 214/255.0, blue: 214/255.0, alpha: 1)
        static let exp_color7 = UIColor( red: 255/255.0, green: 147/255.0, blue: 0/255.0, alpha: 1)
        static let exp_color8 = UIColor( red: 255/255.0, green: 126/255.0, blue: 121/255.0, alpha: 1)
        static let exp_color9 = UIColor( red: 146/255.0, green: 144/255.0, blue: 0/255.0, alpha: 1)
        static let exp_color10 = UIColor( red: 255/255.0, green: 212/255.0, blue: 121/255.0, alpha: 1)
        static let exp_color11 = UIColor( red: 148/255.0, green: 55/255.0, blue: 255/255.0, alpha: 1)
        static let exp_color12 = UIColor( red: 0/255.0, green: 144/255.0, blue: 81/255.0, alpha: 1)
        static let exp_color13 = UIColor( red: 215/255.0, green: 131/255.0, blue: 255/255.0, alpha: 1)
        static let exp_color14 = UIColor( red: 255/255.0, green: 255/255.0, blue: 105/255.0, alpha: 1)//#ffff69b4
        static let exp_color15 = UIColor( red: 255/255.0, green: 255/255.0, blue: 165/255.0, alpha: 1)//#ffffa500
        static let exp_color16 = UIColor( red: 255/255.0, green: 106/255.0, blue: 90/255.0, alpha: 1)//#ff6a5acd
        static let exp_color17 = UIColor( red: 255/255.0, green: 218/255.0, blue: 165/255.0, alpha: 1)//#ffdaa520
        static let exp_color18 = UIColor( red: 255/255.0, green: 128/255.0, blue: 128/255.0, alpha: 1)//#ff808000
        static let exp_color19 = UIColor( red: 255/255.0, green: 0/255.0, blue: 255/255.0, alpha: 1)//#ff00ffff
        static let exp_color20 = UIColor( red: 255/255.0, green: 60/255.0, blue: 179/255.0, alpha: 1)//#ff3cb371
        static let exp_color21 = UIColor( red: 255/255.0, green: 139/255.0, blue: 69/255.0, alpha: 1)//#ff8b4513
        static let exp_color22 = UIColor( red: 255/255.0, green: 255/255.0, blue: 99/255.0, alpha: 1)//#ffff6347
        static let exp_color23 = UIColor( red: 255/255.0, green: 0/255.0, blue: 128/255.0, alpha: 1)//#ff008080
        static let exp_color24 = UIColor( red: 255/255.0, green: 147/255.0, blue: 112/255.0, alpha: 1)//#ff9370db
        static let exp_color25 = UIColor( red: 255/255.0, green: 148/255.0, blue: 0/255.0, alpha: 1)//#ff9400d3
    }
    
    struct ModeNames {
        static let water_presure 	= NSLocalizedString("water_presure", comment: "")
        static let vacuum_cleaner   = NSLocalizedString("vacuum_cleaner", comment: "")
        static let disk_clean       = NSLocalizedString("disk_clean", comment: "")
        static let foam             = NSLocalizedString("foam", comment: "")
        static let hand_water       = NSLocalizedString("hand_water", comment: "")
        static let winter           = NSLocalizedString("winter", comment: "")
        static let vax              = NSLocalizedString("vax", comment: "")
        static let air              = NSLocalizedString("air", comment: "")
        static let carpet_clean     = NSLocalizedString("carpet_clean", comment: "")
        static let osmosis          = NSLocalizedString("osmosis", comment: "")
        static let tire             = NSLocalizedString("tire", comment: "")
        static let warm_water       = NSLocalizedString("warm_water", comment: "")
        static let antimoshka       = NSLocalizedString("antimoshka", comment: "")
    }
    
    struct PropNames {
        static let post_info_segue 				= "PostInfoSegue"
        static let post_modes_segue 			= "PostModesSegue"
        static let post_automodes_segue 		= "PostAutomodesSegue"
        static let post_chart_segue 			= "PostChartSegue"
        static let expenses_car_chart_segue 	= "CarExpensesChart"
        static let expenses_total_chart_segue 	= "TotalExpensesChart"
        static let expenses_car_table_segue 	= "CarExpensesTable"
        static let expenses_total_table_segue 	= "TotalExpensesTable"
        static let post_cell 					= "PostCell"
        static let consumption 					= NSLocalizedString("Consumption", comment: "")
        static let sum 							= NSLocalizedString("Sum", comment: "")
        static let time 						= NSLocalizedString("Time", comment: "")
        static let currency 					= NSLocalizedString("uah", comment: "")
        static let liter 						= NSLocalizedString("l", comment: "")
		static let m3 							= NSLocalizedString("m3", comment: "")
		static let cost_units 					= NSLocalizedString("uah/m3", comment: "")
		static let cost_el_units 				= NSLocalizedString("uah/kWt", comment: "")
		static let kWt 							= NSLocalizedString("kWt", comment: "")
		static let num 							= NSLocalizedString("num", comment: "")
        static let title                        = NSLocalizedString("Title", comment: "")
        static let value                        = NSLocalizedString("Value", comment: "")
        static let units                        = NSLocalizedString("Units", comment: "")
    }
	
	struct ExpensesMoldFields {
        static let rent 					= NSLocalizedString("Rent", comment: "")
        static let salary 					= NSLocalizedString("Salary", comment: "")
		static let water_drain_consumption 	= NSLocalizedString("Water, drain (consumption)", comment: "")
		static let water_drain_cost 		= NSLocalizedString("Water+drain (cost)", comment: "")
		static let water_drain_calculation 	= NSLocalizedString("Water+drain (calculation)", comment: "")
		static let chemistry 				= NSLocalizedString("Chemistry", comment: "")
		static let electricity_consumption 	= NSLocalizedString("Electricity (consumption)", comment: "")
		static let electricity_cost 		= NSLocalizedString("Electricity (cost)", comment: "")
		static let electricity_calculation 	= NSLocalizedString("Electricity (calculation)", comment: "")
		static let additional_equipment 	= NSLocalizedString("Additional equipment", comment: "")
		static let promotions 				= NSLocalizedString("Promotions", comment: "")
		static let number_of_cars 			= NSLocalizedString("Car numbers", comment: "")
		static let money 					= NSLocalizedString("Money", comment: "")
		static let average_bill 			= NSLocalizedString("Average bill", comment: "")
		static let additonal_field_1 		= NSLocalizedString("Additional field 1", comment: "")
		static let additonal_field_2 		= NSLocalizedString("Additional field 2", comment: "")
		static let additonal_field_3 		= NSLocalizedString("Additional field 3", comment: "")
		static let additonal_field_4 		= NSLocalizedString("Additional field 4", comment: "")
		static let additonal_field_5 		= NSLocalizedString("Additional field 5", comment: "")
		static let additonal_field_6 		= NSLocalizedString("Additional field 6", comment: "")
		static let additonal_field_7 		= NSLocalizedString("Additional field 7", comment: "")
		static let additonal_field_8 		= NSLocalizedString("Additional field 8", comment: "")
		static let additonal_field_9 		= NSLocalizedString("Additional field 9", comment: "")
		static let additonal_field_10 		= NSLocalizedString("Additional field 10", comment: "")
		static let electricity 				= NSLocalizedString("Electricity", comment: "")
		static let water_drain 				= NSLocalizedString("Water+drain", comment: "")
		static let total_expenses 			= NSLocalizedString("Total expenses", comment: "")
	}
	
	struct FieldsMainIds {
		static let MAIN_IDS_COUNT: Int  					= 24
		static let MAIN_ID_RENT: Int  					    = 1
		static let MAIN_ID_SALARY: Int  					= 2
		static let MAIN_ID_WHATER_DRAIN_CONSUMPTION: Int    = 3
		static let MAIN_ID_WHATER_DRAIN_COST: Int  		    = 4
		static let MAIN_ID_WHATER_DRAIN_CALC: Int  		    = 5
		static let MAIN_ID_CHEMISTRY: Int  				    = 6
		static let MAIN_ID_ELECTRICITY_CONSUMPTION: Int  	= 7
		static let MAIN_ID_ELECTRICITY_COST: Int  		    = 8
		static let MAIN_ID_ELECTRICITY_CALC: Int  		    = 9
		static let MAIN_ID_ADD_EQUIPMENT: Int  			    = 10
		static let MAIN_ID_PROMOTIONS: Int  				= 11
		static let MAIN_ID_CAR_NUMBER: Int  				= 12
		static let MAIN_ID_MONEY: Int  					    = 13
		static let MAIN_ID_AVARAGE_RECEIPT: Int  			= 14
		static let MAIN_ID_ADD_FIELD_1: Int  				= 15
		static let MAIN_ID_ADD_FIELD_2: Int  				= 16
		static let MAIN_ID_ADD_FIELD_3: Int  				= 17
		static let MAIN_ID_ADD_FIELD_4: Int  				= 18
		static let MAIN_ID_ADD_FIELD_5: Int  				= 19
		static let MAIN_ID_ADD_FIELD_6: Int  				= 20
		static let MAIN_ID_ADD_FIELD_7: Int  				= 21
		static let MAIN_ID_ADD_FIELD_8: Int  				= 22
		static let MAIN_ID_ADD_FIELD_9: Int  				= 23
		static let MAIN_ID_ADD_FIELD_10: Int  			    = 24
	}
	
	struct FieldsCarIds {
		static let CAR_IDS_COUNT: Int  		    = 16
        static let CAR_ID_ELECTRICITY: Int      = 25
		static let CAR_ID_WHATER_DRAIN: Int  	= 26
		static let CAR_ID_CHEMISTRY: Int  	    = 27
		static let CAR_ID_SALARY: Int  		    = 28
		static let CAR_ID_RENT: Int  			= 29
		static let CAR_ID_TOTAL_EXPENSE: Int    = 30
		static let CAR_ID_ADD_FIELD_1: Int  	= 31
		static let CAR_ID_ADD_FIELD_2: Int  	= 32
		static let CAR_ID_ADD_FIELD_3: Int  	= 33
		static let CAR_ID_ADD_FIELD_4: Int  	= 34
		static let CAR_ID_ADD_FIELD_5: Int  	= 35
		static let CAR_ID_ADD_FIELD_6: Int  	= 36
		static let CAR_ID_ADD_FIELD_7: Int  	= 37
		static let CAR_ID_ADD_FIELD_8: Int  	= 38
		static let CAR_ID_ADD_FIELD_9: Int  	= 39
		static let CAR_ID_ADD_FIELD_10: Int  	= 40
	}
    
    struct defaultsKeys {
        static let expensesCurrentMonth = "expensesCurrentMonth"
        static let expensesCurrentYear = "expensesCurrentYear"
    }
    
    struct expensesTypes {
        static let MAIN = "MAIN"
        static let ONE_CAR = "ONE_CAR"
    }
}
