struct ValuesByPeriodResponse: Codable{
    var _id : String
    var total : Int
    
    func getDoubleTotalValue() -> Double {
        return Double(total / 1000)
    }
}

