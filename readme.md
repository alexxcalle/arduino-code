# Sistema de Monitoreo de Calidad Ambiental

Este proyecto implementa un sistema de monitoreo de calidad ambiental utilizando Arduino. El sistema mide temperatura, humedad, niveles de CO2 y CO, y calcula un índice de calidad ambiental basado en estos parámetros.

## Parámetros utilizados

- Temperatura (°C)
- Humedad (%)
- Nivel de CO2 (ppm)
- Nivel de CO (ppm)

El índice de calidad ambiental se calcula considerando estos parámetros, con mayor peso en los niveles de CO2 y CO.

## Componentes necesarios

- Arduino (cualquier modelo compatible)
- Sensor DHT11 (temperatura y humedad)
- Sensor MQ135 (CO2)
- Sensor MQ7 (CO)
- LEDs (verde, amarillo, rojo)
- Buzzer
- Interruptor

## Configuración de pines

- DHT11: Pin 9
- MQ135: Pin 11
- MQ7: Pin 10
- LED Verde: Pin 6
- LED Amarillo: Pin 5
- LED Rojo: Pin 4
- Buzzer: Pin 8
- Interruptor: Pin 7

## Cómo utilizar

1. Descarga el código desde este repositorio.
2. Abre el archivo `.ino` en el Arduino IDE.
3. Conecta los componentes según la configuración de pines especificada.
4. Sube el código a tu Arduino.
5. El sistema comenzará a monitorear cuando el interruptor esté activado.

## Funcionamiento

- El sistema lee los sensores cada 2 segundos cuando el interruptor está activado.
- Calcula un índice de calidad ambiental basado en las lecturas.
- Activa diferentes LEDs según la calidad del aire:
  - Verde: Buena calidad
  - Amarillo: Calidad moderada
  - Rojo: Mala calidad (también activa el buzzer)
- Los resultados se imprimen en el monitor serial.

## Cómo editar

Para modificar el código:

1. Abre el archivo en el Arduino IDE.
2. Puedes ajustar los umbrales de calidad del aire en la función `calcularIndiceCalidad()`.
3. Modifica los mapeos de los sensores en `leerSensores()` si usas sensores diferentes.
4. Cambia los pines en las definiciones al principio del código si tu configuración de hardware es diferente.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue para discutir cambios mayores antes de crear un pull request.


## Links adicionales

CRUD con los parametros: https://github.com/alexxcalle/landing-page-piensa
Pagina web de nuestro proyecto: https://github.com/alexxcalle/agency-landing-page-Astrojs
