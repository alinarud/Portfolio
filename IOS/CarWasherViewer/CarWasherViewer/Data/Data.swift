struct Data: Codable, Equatable {

    let modes : [ModeData]
    var updated_at : Int = 0

    static func == (lhs: Data, rhs: Data) -> Bool {
        return
            lhs.updated_at == rhs.updated_at &&
            lhs.modes == rhs.modes
    }
}
