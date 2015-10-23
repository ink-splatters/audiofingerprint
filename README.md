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
4. install boost development package (on mac os x just 'brew install boost',
   on Ubuntu please install package libboost-all-dev)
5. run sudo ./install_gnsdk_libs.sh to make symlinks for GNSDK libs and install them  toldconfig aware folder (on Linux)
6. run ./build.sh 
7. The program will build and will run with sample data (user id, user tag, license and input file Smells Like a Teen Spirit)
8. Please run ./build/install/AudioFingerPrint --help for options
9. To print to stdout, just disable --output parameter. KNOWN ISSUE: in case of error software tries to output
the error message in json format as well. But it seems GNSDK logger has an issue and it works not very well.
10. To deploy the app outside of build machine please use install folder and ensure you have boost same version installed on your system

NOTES

-The software autodetects WAV format (channels, frequency, bps)
-The software uses single result approach: stream.Options().ResultSingle(true); If you want more results, there should be false.
 Please note that other results are not accurate

FILE FORMATS

1. Please see settings_af.json to see input settings format
2. Please see build/install/output.json for output format in case --output is specified
3. Please see stdout in case --output is not specified