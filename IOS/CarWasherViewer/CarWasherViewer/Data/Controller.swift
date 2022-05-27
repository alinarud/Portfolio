import Foundation

struct Controller: Codable {
    var discount_money : Int? = 0
    let modes : [Mode]
    var encashment_money : Int? = 0
    var created : Int
    var pump2_time : Int? = 0
    var description : String?
    var active : Bool
    let automodes : [Automode]
    var updated_by_web : Bool
    var title : String?
    var version : String?
    var total_modes_money : Int? = 0
    var pump1_time : Int? = 0
    var updated_at : Int? = 0
    var __v : Int
    var _id : String
    var id : String
    var _user : String
    var total_money : Int? = 0
    var free_usage_time : Int? = 0
    var comment : String?
    var serial_number : String?
    
    func getLastConnectionDate() -> String {
        let date = Date(timeIntervalSince1970: TimeInterval((updated_at ?? 0) / 1000))
        let df = DateFormatter()
        df.timeZone = .current
        df.timeStyle = DateFormatter.Style.medium
        df.dateFormat = "dd.MM.yyyy HH:mm"
        let str = df.string(from: date)
        
        return str
    }
    
    func getEncashmentMoney() -> Double {
        return Double(Double(encashment_money ?? 0) / 100)
    }
    
    func getTotalMoney() -> Double {
        return Double(Double(total_money ?? 0) / 100)
    }
    
    func getDiscountMoney() -> Double {
        return Double(Double(discount_money ?? 0) / 100)
    }
    
    func getTotalModesMoney() -> Double {
        return Double(Double(total_modes_money ?? 0) / 100)
    }
}
