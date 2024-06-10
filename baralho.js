const baralho = []
let opcao = ""

do{
    opcao = prompt(
        "Cartas no baralho: "+ baralho.length +
        "\n1. Adidiconar uma carta\n2. puxar uma carta\n3. Sair"
    )

    switch(opcao){
        case "1":
            const novaCarta = prompt("Qual é a carta")
            baralho.push(novaCarta)
            break
        case "2":
            const cartaPuxada = varalho.pop()
            if(!cartaPuxada){
                alert("nao ah carta")
            }else{
                alert("voce puxou uma " + cartaPuxada)
            }
        case "3":
            alert("saindo")
            break

        default:
            alert("Opcao Invalida")
    }
}while(opcao !== "3")
