struct Api {
	static let SERVER_URL = "http://185.69.153.20:5000"

    struct AUTH {
        static let URL_LOGIN = "/api/login"
        static let URL_REGISTER = "/api/register"
    }

    struct CONTROLLER {
        static let URL_POSTS = "/api/posts"
        static let URL_POSTS_USER = URL_POSTS + "/user/"
        static let URL_VALUE_BY_PERIOD = URL_POSTS + "/packages/value-by-period"
        static let URL_CONTROLLERS = "/api/controllers"
        static let URL_CONTROLLER_ID = URL_CONTROLLERS

        static let URL_CONTROLLER_MODE = URL_CONTROLLERS
        static let URL_CONTROLLER_AUTOMODE = URL_CONTROLLERS
    }

    struct USER {
        static let URL_USERS = "/api/users"
        static let URL_USER_ID = "/api/users/{userId}"
    }

    struct EXPENSES {
        static let URL_EXPENSES = "/api/expenses"
    }

    struct PARAMETERS {
        static let ID = "id"
        static let TITLE = "title"
        static let DESCRIPTION = "description"
        static let ACTIVE = "active"
        static let COMMENT = "comment"
        static let AUTO_MODE_TIME = "auto_mode_time"
        static let AUTO_MODE_DELAY = "auto_mode_delay"
        static let MODE_MONEY = "mode_money"
        static let MODE_TIME = "mode_time"
        static let MODE_WATER = "mode_water"
        static let MODE_ENERGY = "mode_energy"
        static let MODE_CHEMICAL = "mode_chemical"
        static let MODE_COST = "mode_cost"
        static let MODE_PAY_DELAY = "mode_pay_delay"
        static let TOTAL_MONEY = "total_money"
        static let ENCASHMENT_MONEY = "encashment_money"
        static let DISCOUNT_MONEY = "discount_money"
        static let UPDATE_AT = "update_at"
        static let PUMP1_TIME = "pump1_time"
        static let PUMP2_TIME = "pump2_time"
        static let FREE_USAGE_TIME = "free_usage_time"
        static let VERSION = "version"
    }
}
