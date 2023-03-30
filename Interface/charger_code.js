// Récupération de l'élément "textarea"
function send_code() {
    for(let i=0;i<2;i++){
        var textarea = document.getElementById("codearea");

        // Accès au contenu de la balise "textarea"
        var content = textarea.value;
        let _data = {
            contenu : content,
            num : 1}

        fetch('http://localhost:5000/input',{
            method: "POST",
            body: JSON.stringify(_data),
            headers: {"Content-type": "application/json; charset=UTF-8"}})

        for(let i=0;i<10;i++){
            location.reload(true)
        }

    }


}

