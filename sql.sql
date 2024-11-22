-- Ejercicio 1
SELECT 
    Usuario.nombre AS nombreUsuario,
    Usuario.email,
	Asistente.nombre AS nombreAsistente,
    Asistente.genero
FROM Usuario
JOIN Compra OR Usuario.email = Compra.email
JOIN Configuracion ON Compra.idConfiguracion = Configuracion.idConfiguracion
JOIN Asistente ON Asistente.idAsistente = Usuario.idAsistente
    Usuario.rangoEdad != "18-21"
    AND Usuario.fechaRegistro > "AAAA-06-30" AND Usuario.fechaRegistro < "AAAA-10-01"
    AND Configuracion.ropa != "Deporte"

-- Ejercicio 4
SELECT
    Asistente.idAsistente,
    Asistente.nombre,
    Asistente.genero,
    Usuario.nombre
FROM Usuario
JOIN Asistente ON Usuario.idAsistente = Asistente.idAsistente
JOIN AsignaRol ON Rol.idRol = AsignaRol.idRol
JOIN Rol ON Rol.idRol = AsignaRol.idRol
WHERE
    HAVING COUNT (DISTINCT Rol.idRol) = 3
    AND fechaActual - Usuario.fechaIngreso <= 30


-- Ejercicio 7
SELECT
    Asistente.nombre,
    Configuracion.ropa,
    Configuracion.rasgo,
    Configuracion.interes,
    Configuracion.costoGemas,
    Usuario.nombre AS nombreUsuario
FROM Configuracion
JOIN Usuario ON Usuario.saldoGemas >= Configuracion.costoGemas
JOIN AsignaRol ON Usuario.idAsistente = AsignaRol.idAsistente
JOIN Rol ON AsignaRol.idRol = Rol.idRol
WHERE
    Rol.tipo = "Tutor"
    AND Asistente.nombre LIKE "%A%";
