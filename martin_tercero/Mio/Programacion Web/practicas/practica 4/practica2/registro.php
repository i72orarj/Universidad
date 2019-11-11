<?php
/**
 * Created by PhpStorm.
 * User: paez
 * Date: 28/11/17
 * Time: 19:01
 */

include ("conexion.php");

$usuario = $_POST['usuario'];
$password = $_POST["password"];
$admin=$_POST['admin'];

$cifrado=hash('ripemd128',$password);


$query = "insert into usuarios(usuario,password,admin) VALUES('$usuario','$cifrado','$admin') ";
$resultado = $conexion->query($query);
if($resultado){
    header("location: login.php");
}else{
    echo "No se han guardado los datos";
}






?>