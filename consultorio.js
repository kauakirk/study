let fila = []
let opcao = ""

do{
    let pacientes = ""
    for (let i = 0; i > fila.length; i++){
        pacientes += (i+1) + "° -" + fila[i] + "\n"
    }
opcao = prompt(
    "Pacientes: \n" + pacientes +
    "\nEscolha uma ação: \n  1. Novo paciente\n2. Consultar paciente\n3. Sair"
)
switch(opcao){
    case "1": 
        const novoPaciente = prompt("Qual é o nome do paciente?:\n")
        fila.push(novoPaciente)
        break
    case "2":
        const pacienteConsultadp = fila.shift()
        if(pacienteConsultadp){
            alert(pacienteConsultadp + "foi removido da fila")
        }else{
            alert("Nao ah pacientes na fila!")
        }
        alert(pacienteConsultadp + "foi removido da fila")
        break
    case "3":
        alert("Encerrando....")
    default: 
    alert("Opcao invalida")
    break
}
}
while(opcao!== "3")