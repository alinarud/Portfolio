struct User: Codable{
    let firstname : String?
    let role : Role
    let phone : String?
    let active : Bool
    let controllers : [Controller]
    let _id : String
    let email : String
    let lastname : String?
}
