struct ExpensesResponse: Codable{
    var createdAt : String
    var month : Int
    var year : Int
    var __v : Int
    var _id : String
    var _user : String
    var fields : [Fields]
    var updatedAt : String	
	
    var totalFields : [Fields]?
	var carFields : [Fields]?
	
    public mutating func getTotalFields() -> [Fields] {
        // always return default numbers of rows, field may be without values
        self.totalFields = getDefaultTotalFieldsArray()
        
		for i in 0...((fields.count) - 1) {
            let field: Fields = fields[i]
            
			let type = field.type
			if (type == "MAIN") {
                // update field data
                for j in 0...((self.totalFields?.count ?? 0) - 1) {
                    let fld = self.totalFields?[j]
                    if (fld?.id == field.id) {
                        totalFields?[j] = field
                    }
                }
			}
		}
        
        return self.totalFields!
	}
    
    private func getDefaultTotalFieldsArray() -> [Fields] {
        var arr = [Fields]()
        
        for i in 0...(Constants.FieldsMainIds.MAIN_IDS_COUNT) {
            var field = Fields()
            field.id = String(i)
            switch i {
            case Constants.FieldsMainIds.MAIN_ID_RENT:
                field.title  = Constants.ExpensesMoldFields.rent
            case Constants.FieldsMainIds.MAIN_ID_SALARY:
                field.title  = Constants.ExpensesMoldFields.salary
            case Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CONSUMPTION:
                field.title  = Constants.ExpensesMoldFields.water_drain_consumption
            case Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_COST:
                field.title  = Constants.ExpensesMoldFields.water_drain_cost
            case Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CALC:
                field.title  = Constants.ExpensesMoldFields.water_drain_calculation
            case Constants.FieldsMainIds.MAIN_ID_CHEMISTRY:
                field.title  = Constants.ExpensesMoldFields.chemistry
            case Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CONSUMPTION:
                field.title  = Constants.ExpensesMoldFields.electricity_consumption
            case Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_COST:
                field.title  = Constants.ExpensesMoldFields.electricity_cost
            case Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CALC:
                field.title  = Constants.ExpensesMoldFields.electricity_calculation
            case Constants.FieldsMainIds.MAIN_ID_ADD_EQUIPMENT:
                field.title  = Constants.ExpensesMoldFields.additional_equipment
            case Constants.FieldsMainIds.MAIN_ID_PROMOTIONS:
                field.title  = Constants.ExpensesMoldFields.promotions
            case Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER:
                field.title  = Constants.ExpensesMoldFields.number_of_cars
            case Constants.FieldsMainIds.MAIN_ID_MONEY:
                field.title  = Constants.ExpensesMoldFields.money
            case Constants.FieldsMainIds.MAIN_ID_AVARAGE_RECEIPT:
                field.title  = Constants.ExpensesMoldFields.average_bill
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_1:
                field.title  = Constants.ExpensesMoldFields.additonal_field_1
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_2:
                field.title  = Constants.ExpensesMoldFields.additonal_field_2
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_3:
                field.title  = Constants.ExpensesMoldFields.additonal_field_3
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_4:
                field.title  = Constants.ExpensesMoldFields.additonal_field_4
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_5:
                field.title  = Constants.ExpensesMoldFields.additonal_field_5
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_6:
                field.title  = Constants.ExpensesMoldFields.additonal_field_6
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_7:
                field.title  = Constants.ExpensesMoldFields.additonal_field_7
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_8:
                field.title  = Constants.ExpensesMoldFields.additonal_field_8
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_9:
                field.title  = Constants.ExpensesMoldFields.additonal_field_9
            case Constants.FieldsMainIds.MAIN_ID_ADD_FIELD_10:
                field.title  = Constants.ExpensesMoldFields.additonal_field_10
            default: break
                
            }
            arr.append(field)
        }
        
        return arr
    }
	
    public mutating func getOneCarFields() -> [Fields] {
        self.carFields = getDefaultOneCarFieldsArray()
        
		for i in 0...(fields.count - 1) {
			let field: Fields = fields[i]

			let type = field.type
			if (type == "ONE_CAR") {
                for j in 0...((self.carFields?.count ?? 0) - 1) {
                    let fld = self.carFields?[j]
                    if (fld?.id == field.id) {
                        carFields?[j] = field
                    }
                }
			}
		}
        
        return self.carFields!
	}
	
    private func getDefaultOneCarFieldsArray() -> [Fields] {
        var arr = [Fields]()
        var field = Fields()
        field.id = String(0)
        arr.append(field)
        
        for i in 0...(Constants.FieldsCarIds.CAR_IDS_COUNT) {
            var field = Fields()
            
            switch (i + Constants.FieldsCarIds.CAR_ID_ELECTRICITY) {
            case Constants.FieldsCarIds.CAR_ID_ELECTRICITY:
                field.title  = Constants.ExpensesMoldFields.electricity
                field.id = String(Constants.FieldsCarIds.CAR_ID_ELECTRICITY)
                break
            case Constants.FieldsCarIds.CAR_ID_WHATER_DRAIN:
                field.title  = Constants.ExpensesMoldFields.water_drain
                field.id = String(Constants.FieldsCarIds.CAR_ID_WHATER_DRAIN)
                break
            case Constants.FieldsCarIds.CAR_ID_CHEMISTRY:
                field.title  = Constants.ExpensesMoldFields.chemistry
                field.id = String(Constants.FieldsCarIds.CAR_ID_CHEMISTRY)
                break
            case Constants.FieldsCarIds.CAR_ID_SALARY:
                field.title  = Constants.ExpensesMoldFields.salary
                field.id = String(Constants.FieldsCarIds.CAR_ID_SALARY)
                break
            case Constants.FieldsCarIds.CAR_ID_RENT:
                field.title  = Constants.ExpensesMoldFields.rent
                field.id = String(Constants.FieldsCarIds.CAR_ID_RENT)
                break
            case Constants.FieldsCarIds.CAR_ID_TOTAL_EXPENSE:
                field.title  = Constants.ExpensesMoldFields.total_expenses
                field.id = String(Constants.FieldsCarIds.CAR_ID_TOTAL_EXPENSE)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_1:
                field.title  = Constants.ExpensesMoldFields.additonal_field_1
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_1)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_2:
                field.title  = Constants.ExpensesMoldFields.additonal_field_2
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_2)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_3:
                field.title  = Constants.ExpensesMoldFields.additonal_field_3
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_3)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_4:
                field.title  = Constants.ExpensesMoldFields.additonal_field_4
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_4)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_5:
                field.title  = Constants.ExpensesMoldFields.additonal_field_5
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_5)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_6:
                field.title  = Constants.ExpensesMoldFields.additonal_field_6
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_6)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_7:
                field.title  = Constants.ExpensesMoldFields.additonal_field_7
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_7)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_8:
                field.title  = Constants.ExpensesMoldFields.additonal_field_8
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_8)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_9:
                field.title  = Constants.ExpensesMoldFields.additonal_field_9
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_9)
                break
            case Constants.FieldsCarIds.CAR_ID_ADD_FIELD_10:
                field.title  = Constants.ExpensesMoldFields.additonal_field_10
                field.id = String(Constants.FieldsCarIds.CAR_ID_ADD_FIELD_10)
                break
            default: break
                
            }
            arr.append(field)
        }
        
        return arr
    }
    
    public mutating func updateTotalExpensesFieldValue(fieldId: String, value: String) {
        // find field in  list and change value
        // update all connected fields

        for i in 0...(self.fields.count - 1) {
            var field = fields[i]
            if (field.id == fieldId) {
                field.value = value
                self.fields[i] = field
                break;
            }
        }
		
		// MAIN_ID_WHATER_DRAIN_CONSUMPTION or MAIN_ID_WHATER_DRAIN_COST
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CONSUMPTION || Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_COST) {
			updateTotalWaterDrain();
			return;
		}
		
		// MAIN_ID_ELECTRICITY_CONSUMPTION or MAIN_ID_ELECTRICITY_COST
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CONSUMPTION || Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_COST) {
			updateTotalElectricity();
			return;
		}
		
		// MAIN_ID_RENT
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_RENT) {
			updateCarRent();
			return;
		}
		
		// MAIN_ID_SALARY
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_SALARY) {
			updateCarSalary();
			return;
		}
		
		// MAIN_ID_CHEMISTRY
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_CHEMISTRY) {
			updateCarChemistry();
			return;
		}
		
		// MAIN_ID_CAR_NUMBER
        if (Int(fieldId ) == Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER) {
			updateMainAvarageReceipt();
			updateCarFields();
			return;
		}
    }

    public func updateTotalExpensesFieldName(fieldId: String, name: String) {
        // find field in  list and change field name
        // update all connected fields
        var field: Fields? = getTotalFieldById(fieldId: fieldId);
        field?.title = name;
    }
	
    private mutating func updateTotalWaterDrain() {
        let fld1: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_COST))

        let fld2: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CONSUMPTION))

		let result = (fld1?.getDoubleValue() ?? 0) * (fld2?.getDoubleValue() ?? 0)

        for i in 0...(self.fields.count - 1) {
            var field = fields[i]
            if (field.id == String(Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CALC)) {
                field.value = String(result)
                self.fields[i] = field
                break;
            }
        }
	}
	
    private mutating func updateCarRent() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainRent: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_RENT))

		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainRent?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_RENT)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break;
                }
            }
        }
        
		updateCarTotalExpenses();
    }
	
    private mutating func updateCarSalary() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainSalary: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_SALARY))
		
		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))
		
        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainSalary?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_SALARY)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break;
                }
            }
        }
        
		updateCarTotalExpenses();
    }
	
    private mutating func updateCarWaterDrain() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainWaterDrain: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CALC))

		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainWaterDrain?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)

            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_WHATER_DRAIN)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break;
                }
            }
        }

		updateCarTotalExpenses();
    }
	
    private mutating func updateCarElectricity() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainElectricity: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CALC))

		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
        
            let result = (fldMainElectricity?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_ELECTRICITY)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break;
                }
            }
        }
        
		updateCarTotalExpenses();
    }
	
    private mutating func updateCarChemistry() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainChemistry: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CHEMISTRY))
		
		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainChemistry?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_CHEMISTRY)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break;
                }
            }
        }
        
		updateCarTotalExpenses();
    }
	
    private mutating func updateCarTotalExpenses() {
		var result: Double = 0.0
        for i in 0...(self.fields.count - 1) {
            let field = fields[i]
            if (Int(field.id ?? "") == Constants.FieldsCarIds.CAR_ID_TOTAL_EXPENSE || field.type == Constants.expensesTypes.MAIN) {
				continue;
            }
			
            let val = Double(field.value ?? "")
            result = result + (val ?? 0.0)
		}
		
        for i in 0...(self.fields.count - 1) {
            var field = fields[i]
            if (field.id == String(Constants.FieldsCarIds.CAR_ID_TOTAL_EXPENSE)) {
                field.value = String(result)
                self.fields[i] = field
                break
            }
        }
	}
	
    private mutating func updateTotalElectricity() {
        let fld1: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CONSUMPTION))
		
		let fld2: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_COST))

        let val1 = Double(fld1?.value ?? "0")
        let val2 = Double(fld2?.value ?? "0")
        let result = (val1 ?? 0.0) * (val2 ?? 0.0)
        
        for i in 0...(self.fields.count - 1) {
            var field = fields[i]
            if (field.id == String(Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CALC)) {
                field.value = String(result)
                self.fields[i] = field
                break
            }
        }
        
        updateCarElectricity()
	}

    private mutating func updateMainAvarageReceipt() {
        // find field in  list and change field name
        // update all connected fields
        let fldMainMoney: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_MONEY))

		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainMoney?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsMainIds.MAIN_ID_AVARAGE_RECEIPT)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break
                }
            }
        }
    }
	
    private mutating func updateCarFields() {
        updateCarWaterDrain()
		updateCarChemistry()
		updateCarSalary()
		updateCarRent()
		
        // find field in  list and change field name
        // update all connected fields
        let fldMainSalary: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_SALARY))

		let fldCountCar: Fields? = getTotalFieldById(fieldId: String(Constants.FieldsMainIds.MAIN_ID_CAR_NUMBER))

        if (fldCountCar?.getIntValue() != 0) {
            let result = (fldMainSalary?.getDoubleValue() ?? 0) / (fldCountCar?.getDoubleValue() ?? 0)
            
            for i in 0...(self.fields.count - 1) {
                var field = fields[i]
                if (field.id == String(Constants.FieldsCarIds.CAR_ID_SALARY)) {
                    field.value = String(result)
                    self.fields[i] = field
                    break
                }
            }
        }
        
		updateCarTotalExpenses()
    }
	
	private func getTotalFieldById(fieldId: String) -> Fields? {
        for i in 0...(self.fields.count - 1) {
            let field = fields[i]
            if (field.id != fieldId) {
                continue
            }
            
            return field
        }
		
        return nil
	}


    public func updateCarExpensesFieldName(fieldId: String, name: String) {
        // find field in  list and change field name
        // update all connected fields
        var fld: Fields? = getCarFieldById(fieldId: fieldId)

        fld?.title = name
    }

    public func updateCarExpensesFieldValue(fieldId: String, value: String) {
        // find field in  list and change value
        // update all connected fields
        var fld: Fields? = getCarFieldById(fieldId: fieldId);
	
        fld?.value = value
    }

	private func getCarFieldById(fieldId: String) -> Fields? {
        for i in 0...(self.carFields?.count ?? 0) {
            let field = carFields?[i]
            if (field?.id != fieldId) {
				continue;
            }

			return field
		}
		return nil
	}
}
