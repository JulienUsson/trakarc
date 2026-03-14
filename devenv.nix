{
  pkgs,
  lib,
  config,
  ...
}: {
  packages = with pkgs; [
    alejandra
    platformio
    avrdude
    libusb1
  ];

  env.PLATFORMIO_CORE_DIR = "${config.devenv.root}/.pio";

  scripts.flash.exec = "pio run --target upload";
  scripts.monitor.exec = "pio device monitor";

  enterShell = ''
    echo "--- Environnement M5StickC PLUS2 (devenv) ---"
    pio --version
  '';

  languages.python.enable = true;
}
