import csv
import sys

def calcular_y_guardar_estadisticas(archivo_csv, archivo_salida):
    duraciones_desvios = []
    duraciones_bolsa = []
    detenciones = 0
    
    # Estados para el desvío de caudal (alarma)
    orden_actual = None
    en_desvio = False
    tiempo_inicio_desvio = None
    
    # Estados para fin de bolsa
    tiempo_fin_bolsa = None
    esperando_detencion_por_bolsa = False  # Cambiado para reflejar la nueva lógica
    
    # Estados para las detenciones
    causa_detencion_activa = False
    
    # Estados para porcentaje de tiempo en rango
    caudal_actual = None
    ultimo_tiempo = None
    tiempo_total = 0.0
    tiempo_en_rango = 0.0

    with open(archivo_csv, 'r') as file:
        reader = csv.DictReader(file)
        
        for row in reader:
            t = float(row['Time'])
            tipo = row['Signal_Type']
            valor = float(row['Value'])
            
            # --- Lógica de acumulación de tiempo (Porcentaje en rango) ---
            if ultimo_tiempo is not None:
                dt = t - ultimo_tiempo
                tiempo_total += dt
                
                if orden_actual is not None and orden_actual > 0 and caudal_actual is not None:
                    desvio = abs(caudal_actual - orden_actual) / orden_actual
                    if desvio <= 0.10:
                        tiempo_en_rango += dt
            
            # --- Procesamiento del evento actual ---
            if tipo == 'ORDEN_MEDICA':
                orden_actual = valor
                
            elif tipo == 'CAUDAL_ACTUADOR':
                caudal_actual = valor
                
                # Registro de detenciones por falla (alarma crítica o fin de bolsa)
                if caudal_actual == 0 and causa_detencion_activa:
                    detenciones += 1
                    causa_detencion_activa = False
                
                # NUEVO: Cálculo del intervalo entre fin de bolsa y caudal = 0
                if caudal_actual == 0 and esperando_detencion_por_bolsa:
                    duraciones_bolsa.append(t - tiempo_fin_bolsa)
                    esperando_detencion_por_bolsa = False
                
                # Evaluación de los intervalos de desvío
                if orden_actual is not None and orden_actual > 0:
                    desvio_actual = abs(caudal_actual - orden_actual) / orden_actual
                    condicion_falla = (desvio_actual > 0.10) and (caudal_actual != 0)
                    
                    if condicion_falla and not en_desvio:
                        en_desvio = True
                        tiempo_inicio_desvio = t
                        
                    elif not condicion_falla and en_desvio:
                        duraciones_desvios.append(t - tiempo_inicio_desvio)
                        en_desvio = False
                        
            elif tipo == 'FIN_BOLSA':
                causa_detencion_activa = True
                tiempo_fin_bolsa = t
                esperando_detencion_por_bolsa = True  # Activamos la espera de que el actuador baje a 0
                
            elif tipo == 'ALARMA_CRITICA':
                causa_detencion_activa = True
            
            ultimo_tiempo = t

    # Calculamos el porcentaje final
    porcentaje_en_rango = (tiempo_en_rango / tiempo_total * 100) if tiempo_total > 0 else 0.0

    # --- ESCRITURA DEL ARCHIVO ---
    with open(archivo_salida, 'w') as f:
        # Línea 1: Promedio de respuesta a desvíos
        if duraciones_desvios:
            f.write(f"Tiempo de respuesta promedio a los desvios: {(sum(duraciones_desvios) / len(duraciones_desvios)):.6f}\n")
        else:
            f.write("Tiempo de respuesta promedio a los desvios: NaN\n")
            
        # Línea 2: Promedio de respuesta a fin de bolsa
        if duraciones_bolsa:
            f.write(f"Tiempo de respuesta promedio a los fines de bolsa: {(sum(duraciones_bolsa) / len(duraciones_bolsa)):.6f}\n")
        else:
            f.write("Tiempo de respuesta promedio a los fines de bolsa: NaN\n")
            
        # Línea 3: Cantidad de detenciones (Alarma Crítica / Fin de bolsa)
        f.write(f"Cantidad de detenciones de la bomba: {detenciones}\n")
        
        # Línea 4: Porcentaje de tiempo con caudal dentro del 10%
        f.write(f"Porcentaje de tiempo con infusion correcta respecto al tiempo total de la simulacion: {porcentaje_en_rango:.2f}\n")

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Uso: python calc-statistics.py <ruta_a_archivo.csv> <ruta_salida.txt>")
    else:
        archivo_entrada = sys.argv[1]
        archivo_salida = sys.argv[2]
        calcular_y_guardar_estadisticas(archivo_entrada, archivo_salida)
