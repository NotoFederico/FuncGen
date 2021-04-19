# FuncGen_Firmware

Sistema operativo: Windows 10 / IDE: STM32CUBEIDE / Lenguajes = C, C++

[Enlace al informe](https://github.com/NotoFederico/STM32/blob/main/FuncGen/FuncGen_STM32DISCO/Informe.pdf)

El presente proyecto tiene por objetivo desarrollar un generador de funciones, que es exactamente lo que su nombre implica: un equipo de testeo que genera señales eléctricas en forma de ondas que se utilizan como estímulo para mediciones electrónicas.

La mayoría de los circuitos requieren algún tipo de señal de entrada cuya amplitud varía con el tiempo. La señal puede ser una señal de corriente alterna (con picos que oscilan por encima y por debajo de una referencia) o puede variar en un rango de tensiones de offset de corriente continua, ya sea positivo o negativo. Puede ser una onda sinusoidal u otra función analógica, un pulso digital, un patrón binario o una forma de onda puramente arbitraria.

El generador de señales, o de funciones, es la fuente de estímulo. Se empareja con un instrumento de adquisición de datos para obtener una solución de medición completa. Las dos herramientas se conectan en los terminales de entrada y salida del dispositivo bajo prueba (DUT). 

El generador de señales puede proporcionar formas de onda "ideales" o puede agregar cantidades conocidas y repetibles y tipos de distorsión (o errores) a la señal que entrega. Esta característica es una de las mayores virtudes del generador de señales, ya que a menudo es imposible crear una distorsión predecible, exactamente cuando y donde es necesario, utilizando solo el circuito en sí. La respuesta del dispositivo bajo prueba (DUT) en la presencia de estas señales distorsionadas revela su capacidad para manejar tensiones que caen fuera de la envolvente del rendimiento normal.

Existen cientos de aplicaciones diferentes para esta clase de equipos, pero colocado en un contexto de mediciones electrónicas, se pueden divisar tres categorías: 
Verificación: los diseñadores de equipos inalámbricos que desarrollan nuevo hardware de transmisión y recepción deben simular señales I&Q de banda base, con y sin deficiencias, para verificar la conformidad con los estándares inalámbricos patentados y para ello se usan funciones arbitrarias de baja distorsión.

Caracterización: los convertidores digital a analógico (DAC) y los convertidores analógico a digital (ADC) recientemente desarrollados deben probarse exhaustivamente para determinar sus límites de linealidad y distorsión. Se aplican señales analógicas y digitales en fase para llevar las velocidades de estos dispositivos hasta 1Gbps.
Test de estrés o margen: los ingenieros que trabajan con arquitecturas de flujo de datos en serie (comúnmente utilizadas en buses de comunicaciones digitales) necesitan estresar sus dispositivos con deficiencias, particularmente fluctuaciones y violaciones de sincronización

En el proyecto en cuestión, se podrán generar señales conocidas: como seno, semiverseno, cuadrada, rectangular, triangular, diente de sierra y ruido blanco y señales arbitrarias, que son aquellas señales de origen complejo que no siguen una expresión matemática regular y que podrán ser generadas por el usuario mediante un software especializado y posteriormente enviadas a través de WiFi, gracias a un sitio web dedicado. Dichas señales podrán ser elegidas a través de un menú y sus parámetros, tales como duty, offset y amplitud, son modificables y serán monitoreados en tiempo real en un display.
 
