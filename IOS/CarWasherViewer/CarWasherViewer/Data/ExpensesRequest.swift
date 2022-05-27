struct ExpensesRequest: Codable{
    var year : Int
    var month : Int
    var expenses: [Fields]
}

