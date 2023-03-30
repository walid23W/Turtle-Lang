import {drawTurtle} from "./turtle.js";
import {turtlePath} from "./turtle_path.js";

var canvas = document.getElementById("canva");
export var ctx = canvas.getContext("2d");

ctx.restore()
ctx.clearRect(0, 0, canvas.width, canvas.height)
ctx.save()
ctx.translate(canvas.width / 2, canvas.height / 2)

turtlePath(drawTurtle)
