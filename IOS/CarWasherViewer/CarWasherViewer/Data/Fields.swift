struct Fields: Codable{
    var measure : String?
    var id : String?
    var title : String?
    var type : String?
    var value : String?

    init(measure: String? = nil, id: String? = nil, title: String? = nil, type: String? = nil, value: String? = nil) {
            self.measure = measure
            self.id = id
            self.title = title
        self.type = type
        self.value = value
    }
        
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        measure = try container.decode(String.self, forKey: .measure)
        title = try container.decode(String.self, forKey: .title)
        type = try container.decode(String.self, forKey: .type)
        
        do {
            id = try container.decode(String.self, forKey: .id)
        } catch DecodingError.typeMismatch {
            id = try String(container.decode(Int.self, forKey: .id))
        }
        
        do {
            value = try String(container.decode(Double.self, forKey: .value))
        } catch DecodingError.typeMismatch {
            value = try container.decode(String.self, forKey: .value)
        }
    }
    
	public func getDoubleValue() -> Double {
        let result = Double(value ?? "")
        return result ?? 0.0
	}

    public func getIntValue() -> Int {
        let result = Int(value ?? "")
        return result ?? 0
    }
}
