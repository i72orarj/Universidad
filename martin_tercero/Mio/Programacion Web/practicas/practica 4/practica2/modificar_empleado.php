<?php

include ("conexion.php");

$id = $_POST['id'];
$nombre = $_POST['nombre'];
$apellido =$_POST['apellido'];
$dni = $_REQUEST['dni'];
$dni2=$_POST['antiguo'];

if(isset($_POST['modificar'])){
    $query = "update empleados set id='$id',nombre='$nombre',apellido='$apellido',dni='$dni' where dni='$dni2'";
    $resultado = $conexion->query($query);
    header("location: empleados.php");
}else{
    echo "No se han modificado los datos";
}

if(isset($_POST['cancelar'])){
    header("location: empleados.php");
}
/*$query = "update empleados set id='$id',nombre='$nombre',apellido='$apellido',dni='$dni' where dni='$dni2'";
$resultado = $conexion->query($query);
if($resultado){
    header("location: empleados.php");
}else{
    echo "No se han guardado los datos";
}*/
?>