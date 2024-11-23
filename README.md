# ESP32 BLE Keyboard Emulator

Ein Arduino-basiertes Projekt, das einen ESP32-Mikrocontroller verwendet, um eine Bluetooth Low Energy (BLE) Tastatur zu emulieren. Dieses Projekt ermöglicht es dem ESP32, sich als HID-Gerät (Human Interface Device) bei anderen Geräten anzumelden und Tastatureingaben zu simulieren.

## 🚀 Features

- BLE HID Keyboard Emulation
- Automatische Wiederverbindung bei Verbindungsabbruch
- Unterstützung für alle Standard-Tastatur-Keycodes
- Kompatibel mit verschiedenen Betriebssystemen (Windows, macOS, iOS, Android)
- Niedriger Energieverbrauch durch BLE

## 📋 Voraussetzungen

### Hardware
- ESP32 Development Board (getestet mit ESP32-WROOM-32)
- Micro-USB Kabel
- Computer für die Programmierung

### Software
- Visual Studio Code mit PlatformIO Plugin
- ESP32 Board Support Package
- Erforderliche Bibliotheken:
  - ESP32 BLE Arduino
  - BLE2902 (Teil des ESP32 Arduino Frameworks)

## ⚙️ Installation


1. **Erforderliche Bibliotheken installieren**
   - Öffnen Sie in der Arduino IDE: `Werkzeuge > Bibliotheken verwalten`
   - Suchen und installieren Sie "ESP32 BLE Arduino"

2. **Board Configuration**
   - Wählen Sie in der Arduino IDE:
     - Board: "ESP32 Dev Module"
     - Upload Speed: "921600"
     - CPU Frequency: "240MHz (WiFi/BT)"
     - Flash Frequency: "80MHz"
     - Flash Mode: "QIO"
     - Flash Size: "4MB (32Mb)"
     - Partition Scheme: "Default 4MB with spiffs"

## 📥 Projekt-Setup

1. **Repository klonen**
   ```bash
   git clone https://github.com/IhrUsername/esp32-ble-keyboard.git
   cd esp32-ble-keyboard
   ```

2. **Sketch öffnen**
   - Öffnen Sie die `.ino` Datei in der Arduino IDE
   - Überprüfen Sie die Board-Einstellungen
   - Kompilieren und hochladen Sie den Code

## 🔧 Verwendung

1. Nach dem Hochladen des Codes startet der ESP32 automatisch im Bluetooth-Advertising-Modus
2. Öffnen Sie die Bluetooth-Einstellungen auf Ihrem Zielgerät
3. Suchen Sie nach "ESP32 Keyboard" in der Liste der verfügbaren Geräte
4. Koppeln Sie das Gerät
5. Der ESP32 wird als Tastatur erkannt und kann nun Eingaben senden

### Beispiel-Code anpassen

```cpp
void loop() {
    if(connected) {
        // Sende den Buchstaben 'a' (Keycode 0x04)
        sendKey(0x04);
        delay(2000); // Warte 2 Sekunden
    }
    delay(50);
}
```

## 🔑 Key Codes

Häufig verwendete HID Keycodes:

| Taste | Hexadezimal | Dezimal |
|-------|-------------|---------|
| a-z   | 0x04-0x1D  | 4-29    |
| 0-9   | 0x27-0x30  | 39-48   |
| Enter | 0x28       | 40      |
| Space | 0x2C       | 44      |
| Tab   | 0x2B       | 43      |
| Back  | 0x2A       | 42      |

## 🛠️ Fehlerbehebung

- **ESP32 wird nicht erkannt**
  - Überprüfen Sie das USB-Kabel
  - Installieren Sie ggf. den [CP210x USB to UART Bridge VCP Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

- **Verbindungsprobleme**
  - Stellen Sie sicher, dass Bluetooth auf dem Zielgerät aktiviert ist
  - Überprüfen Sie die Serial-Monitor-Ausgabe (115200 baud)
  - Löschen Sie ggf. vorhandene Bluetooth-Kopplungen und versuchen Sie es erneut

## 📡 Technische Details

Der ESP32 verwendet das BLE HID Over GATT Profil (HOGP) zur Emulation einer Tastatur. Das Projekt nutzt folgende Hauptkomponenten:

- BLE Server für die Verbindungsverwaltung
- HID Service für die Tastatur-Emulation
- Input Report Characteristic für Tastatureingaben
- Standard HID Report Descriptor für Tastatur-Layout

## 🤝 Beitragen

Beiträge sind willkommen! Bitte erstellen Sie einen Fork des Projekts und reichen Sie einen Pull Request ein.

1. Fork des Projekts erstellen
2. Feature Branch erstellen (`git checkout -b feature/AmazingFeature`)
3. Änderungen committen (`git commit -m 'Add some AmazingFeature'`)
4. Branch pushen (`git push origin feature/AmazingFeature`)
5. Pull Request öffnen

## 📝 Lizenz

Dieses Projekt ist unter der MIT Lizenz lizenziert - siehe die [LICENSE.md](LICENSE.md) Datei für Details.

## ✨ Danksagung

- [ESP32 BLE Arduino Library](https://github.com/nkolban/ESP32_BLE_Arduino)
- [Espressif Systems](https://www.espressif.com/)
- Allen Mitwirkenden und Testern

## 📞 Support

Bei Fragen oder Problemen erstellen Sie bitte ein [GitHub Issue](https://github.com/IhrUsername/esp32-ble-keyboard/issues).
