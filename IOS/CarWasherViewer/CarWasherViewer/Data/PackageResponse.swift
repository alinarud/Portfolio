import Foundation

struct PackageResponse: Codable, Equatable {

    var data : Data
    var created : String 
    var _id : String
    
    static func == (lhs: PackageResponse, rhs: PackageResponse) -> Bool {
        return
            lhs._id == rhs._id &&
            lhs.created == rhs.created &&
            lhs.data == rhs.data
    }
    
    func getCreatedDate() -> Date {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"
        let date = dateFormatter.date(from: created)!
        
        let calendar = Calendar.current
        let components = calendar.dateComponents([.year, .month, .day, .hour], from: date)
        
        let resultDate = calendar.date(from: components)!
        return resultDate
    }
}
