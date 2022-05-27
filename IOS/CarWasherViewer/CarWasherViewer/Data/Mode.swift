import Foundation


struct Mode: Codable {
    
    var mode_chemical : Int
    var created : Int
    var mode_money : Int
    var mode_water : Double
    var active : Bool
    var description : String
    var comment : String?
    var title : String
    var mode_pay_delay : Int
    var updated_at : Int
    var mode_energy : Int
    var mode_time : Int
    var id : String
    var _id : String
    var mode_cost : Int
    var status : Status
    
    func getLastConnectionDate() -> String {
        let date = Date(timeIntervalSince1970: TimeInterval(updated_at / 1000))
        let df = DateFormatter()
        df.timeZone = .current
        df.timeStyle = DateFormatter.Style.medium
        df.dateFormat = "dd.MM.yyyy HH:mm"
        let str = df.string(from: date)
        
        return str
    }
    
    func getWorkingTime() -> String {
        let hours = mode_time / 3600
        let minutes = (mode_time % 3600) / 60
        let seconds = (mode_time % 3600) % 60
        
        let strWorkingTime = String(hours) + ":" + String(minutes) + ":" + String(seconds)
        
        return strWorkingTime
    }
    
    func getSpentModey() -> Double {
        return Double(Double(mode_money) / 100)
    }
    
    func getMinuteCost() -> Double {
        return Double(Double(mode_cost) / 100)
    }
    
    func getWaterConsumption() -> Double {
        return Double(Double(mode_water) / 100)
    }
    
    func getChemicalConsumption() -> Double {
        return Double(Double(mode_chemical) / 100)
    }
    
    func getElectricityConsumption() -> Double {
        return Double(Double(mode_energy) / 100)
    }
}
