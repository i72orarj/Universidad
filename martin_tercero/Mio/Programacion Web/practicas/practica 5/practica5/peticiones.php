<?php

    session_start();
    if(!isset($_SESSION["u_usuario"])){

        header("location:login.php");

    }


    include ("conexion.php");

    $resultado=mysqli_query($conexion,"select * from empleados");

    $resultado2=mysqli_query($conexion,"select * from peticiones");


    if($row = mysqli_fetch_array($resultado)){
        $dni = $row["dni"];

    }

    if($peticion=mysqli_fetch_array($resultado2)){

        $dnit = $peticion["solicitud"];
    }

    if($dnit == $dni) {


        echo <<< end_

    
       
    
    
    <div align="center">
            <tr>
                <p><strong>ID: </strong> $row[id]</p>
                <p><strong>nombre: </strong>$row[nombre]</p>
                <p><strong>apellido: </strong>$row[apellido]</p>
                <p><strong>dni: </strong>$row[dni]</p>
                <p><strong>sueldo: </strong>$row[sueldo]</p>
                <p><strong> nuevo sueldo: </strong>$row[solicitud]</p>
                <br/>
            </tr>
     
    
    <form action="acciones.php" method="post">
        <button type="submit" name="aceptar">aceptar</button>
        <button type="submit" name="rechazar">rechazar</button>
    </form>
        <a href="empleados.php">Inicio</a>
    </div>

end_;

    }

?>