function calculate() {
    let x = Number(document.getElementById("x").value);
    let y = Number(document.getElementById("y").value);
    let z = Number(document.getElementById("z").value);
    let ans = (x + y + z) /3;
    document.getElementById("ans").innerHTML = ans;
}