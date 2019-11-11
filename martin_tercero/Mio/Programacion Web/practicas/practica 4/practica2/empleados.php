<?php


session_start();
?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>index</title>
</head>
<body>
<?php



            /*if(!isset($_SESSION["u_usuario"])){

                header("location:login.php");

            }


             $sql = "select * from usuarios where admin=: admin";
             $result=$conexion->query($sql);
             $row=$result['admin'];


            echo "admin: " .$row['admin'] . "<br>";
            echo "Usuario: " .$_SESSION["u_usuario"] . "<br><br>";*/
?>



            <div  style="text-align:center">
                <table border='3' align='center' style="margin: 0 auto;">



                    <head>
                        <tr><th colspan='4'><h2>LISTA DE EMPLEADOS</h2></th></tr>
                        <tr>
                            <th> Empleados </th> <th> Info</th> <th colspan="2">Operaciones</th>
                        </tr>
                    </head>

                    <?php
                    include ("conexion.php");

                    $query="Select * from empleados";
                    $resultado = $conexion->query($query);
                    while($row=$resultado->fetch_assoc()) {
                        echo <<< end_
                        
                    
                    <tr>
                        <td>$row[nombre]</td>
                        <td><a href="infoempleados.php?dni=$row[dni]">ver detalles</a></td>
end_;


                        if ($_SESSION['u_usuario']) {

                            echo <<< _end

                        <td><a href="modificar.php?dni=$row[dni] ">modificar</a></td>
                        <td><a href="eliminar.php?dni=$row[dni] ">eliminar</a></td>
_end;
                        }
                        echo "</tr>";

                    }
            echo     "</table><br/><br/>";

            if($_SESSION['u_usuario']){
                echo <<< _end
               
                <tr>
                    <form action="Insertar.php" method="post">
                        <button type="submit">Añadir</button>
                    </form>

                </tr>
            </div>

<form action="logout.php" method="post">
    <button type="submit">Cerrar session</button>
</form>
_end;


}else{
    echo <<< _end
 <form action="login.php" method="post">
    <button type="submit">Iniciar session</button>
 </form>
_end;
}

?>



</body>
</html>
<?php
/*include ('conexion.php');
$resultado = mysqli_query($conexion,"select * from empleados");
while ($consulta = mysqli_info_array($resultado)){
    echo $consulta['nombre'];
}
include ('cerrarconexion.php');
*/



/*$host="localhost";
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

*/

//$resultado = mysqli_query($conexion,"select nombre,apellidos from empleados");

/*$rows = $conexion->query("select nombre,apellidos from empleados ");
foreach ($rows as $row){
    echo '<td>' .$row["nombre"]; '</td>';
    echo '<br>';
}
include ('cerrarconexion.php');*/

?>
