<?php
/**
 * Created by PhpStorm.
 * User: paez
 * Date: 24/10/17
 * Time: 21:28
 */

" <h1> Fitosanitarios Cordoba </h1>";


//include ('conexion.php');

$host="localhost";
$username = "uco";
$password = "uco";
$database = "empresa";

$conexion= new mysqli($host,$username, $password, $database);
if($conexion->connect_error())
    die ($conexion->error);
$sql = "SELECT * FROM empresa";

$rows = $conexion->query($sql);
    if(!$rows)
        die ($conexion->error);
$row = $rows->fetch_assoc();

echo '<td>' .$row["nombre"]; '</td>'



/*$resultado = mysqli_query($conexion,"select nombre,apellidos from empleados");
$rows = $conexion->query($resultado);
foreach ($rows as $row){
    echo '<td>' .$row["nombre"]; '</td>';
}*/
//include ('cerrarconexion.php');


?>