class Product{
    constructor(name, description, price){
    this.name = name
    this.description = description
    this.price = price
    this.inStock = 0
    }
    
    addToStock(quatity){
        this.inStock += quatity
    }
    calculateDiscount(discount){
        return this.price * ((100 - discount) /100)

    }
}
const watch = new Product ("Relogio", "Gold", "200")