<?php
/**
 * Created by PhpStorm.
 * User: paez
 * Date: 28/11/17
 * Time: 19:56
 */

session_start();
session_destroy();
header("location:index.php");



?>