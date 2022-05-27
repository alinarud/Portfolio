import Foundation

struct Automode: Codable{
    var updated_at : Int
    var created : Int
    var active : Bool
    var description : String?
    var comment : String?
    var auto_mode_delay : Int
    var id : String
    var _id : String
    var title : String
    var auto_mode_time : Int
    var automode : Bool
    var status : Status
    
    func getWorkingTime() -> String {
        let hours = auto_mode_time / 3600
        let minutes = (auto_mode_time % 3600) / 60
        let seconds = (auto_mode_time % 3600) % 60
        
        let strWorkingTime = String(hours) + ":" + String(minutes) + ":" + String(seconds)
        
        return strWorkingTime
    }
}
