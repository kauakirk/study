class User{
    constructor(fullname, email, password){
        this.fullname = fullname
        this.email = email
        this.password = password
    }
    login(email, password){
        if( this.email === email && this.password === password){
            console.log("Login realizado com success")
        }else {
            console.log("erro")
        }
    }
}

const john = new User ("John Doe", "john@gmail.com", "123")
john.login("john@gmail.com", "123")
