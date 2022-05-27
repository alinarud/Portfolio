struct ModeData: Codable, Equatable {
    var mode_pay_delay : Int = 0
    var mode_time : Int = 0
    var mode_id : Int = 0
    var mode_money : Int = 0
    var mode_cost : Int = 0
    
    func getDoubleModeMoney() -> Double {
        let intValue = Int(mode_money) 
        
        let doubleValue = Double(intValue) / 100
        return doubleValue
    }
    
    static func == (lhs: ModeData, rhs: ModeData) -> Bool {
        return
            lhs.mode_pay_delay == rhs.mode_pay_delay &&
            lhs.mode_time == rhs.mode_time &&
            lhs.mode_id == rhs.mode_id &&
            lhs.mode_money == rhs.mode_money &&
            lhs.mode_cost == rhs.mode_cost
    }
}
