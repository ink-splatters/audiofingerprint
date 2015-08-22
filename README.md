AudioFinterprint v1.0


PREREQUISITES
  -gcc/clang (Xcode on Mac, devtools or analog on Linux)
  -cmake
  -boost 1.55+
  -gracenotesdk (GNSDK)

  for installing prerequisites on Mac please use brew
  for installing prerequisites on Linux please use your packet manager

BUILDING

1. Install GracenoteSDK. Note, you should get your App ID and license file from Gracenote.
   Please see settings_af.json for an example
2. set GRACENOTESDK_ROOT ENV variable
3. install cmake
4. install boost development package (on mac os x just 'brew install boost')
5. run ./build.sh 
6. The program will build and will run with sample data (user id, user tag, license and input file Smells Like a Teen Spirit)
7. Please run ./build/install/AudioFingerPrint --help for options

8. To deploy the app outside of build machine please use install folder and ensure you have boost same version installed on your system


NOTES

The software autodetects WAV format (channels, frequency, bps)

FILE FORMATS

1. Please see settings_af.json to see input settings format
2. Please see build/install/output.json for output format 