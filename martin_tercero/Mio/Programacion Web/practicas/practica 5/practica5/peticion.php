<?php

session_start();


if(!isset($_SESSION["u_usuario"])){

    header("location:login.php");

}
?>
<div align="center">

    <h3>Enviar una peticion</h3>
    <form action="enviarpeticion.php" method="post">

        <br/>
        <input type="text" name="id" placeholder="id del empleado" value="" /> <br/><br/>
        <input type="text" required name="dni" placeholder="dni del empleado" value="" /><br/><br/>
        <input type="text" required name="sueldo" placeholder="sueldo que desea" value="" /><br/><br/>
        <input type="submit" value="Enviar">

    </form>
</div>
