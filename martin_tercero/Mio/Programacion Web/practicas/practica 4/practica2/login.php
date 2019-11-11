<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>login</title>
</head>
<body>
<div align="center">

    <h3>Iniciar sesion</h3>
    <hr />

    <form action="valuelogin.php" method="post" >

        <label>Nombre Usuario:</label><br>
        <input name="usuario" type="text" >
        <br><br>

        <label>Password:</label><br>
        <input name="password" type="password">
        <br><br>

        <input type="submit" name="submit"  value="Login">

    </form>
    <hr />

    <h3>Registro</h3>
    <hr />

    <form action="registro.php" method="post" >



        <label>Nombre Usuario:</label><br>
        <input name="usuario" type="text" id="usuario" required>
        <br><br>

        <label>Password:</label><br>
        <input name="password" type="password" id="password" required>
        <br><br>

        <label>Administrador:</label><br>
        <input name="admin" type="text" id="admin" required>
        <br><br>

        <input type="submit" name="submit" value="Registro">

    </form>
    <hr />



</body>
</html>