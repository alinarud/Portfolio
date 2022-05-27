import Foundation

class DeWashDataStorage {

    var loginResponse: LoginResponse?
    var posts: Array<Controller> = []
    var expensesResponse: ExpensesResponse?
    
    weak var delegate: DeWashDataDelegate?
    
	func initPosts() {
        print("init posts");
        let token = loginResponse?.token
        let userId = loginResponse?.user._id
        let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_POSTS_USER + (userId ?? ""))!
        let session = URLSession.shared;
        var request = URLRequest(url: url);

        request.setValue(token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type");
        request.setValue("application/json", forHTTPHeaderField: "Accept");
        request.httpMethod = "GET";
        
        let task = session.dataTask(with: request as URLRequest, completionHandler: { data, response, error in
            
            // set posts into posts variable
            guard let data = data,
                let response = response as? HTTPURLResponse,
                error == nil else {                                              // check for fundamental networking error
                print("error", error ?? "Unknown error")
                return
            }

            guard (200 ... 299) ~= response.statusCode else {                    // check for http errors
                print("statusCode should be 2xx, but is \(response.statusCode)")
                print("response = \(response)")
                
                do {
                    let decoder = JSONDecoder()
                    let errorResponse = try decoder.decode(ErrorResponse.self, from: data)
                    print("Status: \(errorResponse.status)")
                    print("Message: \(errorResponse.message)")
                }
                catch let err {
                    print("\ninit posts Error", err)
                    return;
                }
                return
            }

            print(response)
           
            do {
                let decoder = JSONDecoder()
                self.posts = try decoder.decode(Array<Controller>.self, from: data)
                
                self.delegate?.onDataChanged(dewashData: self)
                
            } catch let err {
                print("\nInit posts Error", err)
                return;
            }        })
        task.resume();
	}
    
    public func getPosts() -> Array<Controller> {
        return self.posts
    }

    public func getToken() -> String {
        return loginResponse?.token ?? ""
    }
    
    public func getController(postId: String?) -> Controller? {
        for controller in self.posts {
            print(controller._id)
            if (postId == controller._id) {
                return controller
            }
        }
        
        return nil
    }
}
