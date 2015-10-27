#
if [ -n "$1" ]; then
 echo "Overriding lib folder name: $1"
 libFolderName=$1
fi
sysName=`uname`
arch=`uname -m`
version=`cat $GRACENOTESDK_ROOT/version`
a=( ${version//./ } )
version="${a[0]}.${a[1]}.${a[2]}"


if [ "$sysName" == "Darwin" ]; then
  sysName="mac"
  echo "You are on Mac $arch"
else
  sysName="linux"
  echo "You are on Linux $arch"
fi

if [ -z "$libFolderName" ]; then
    if [ "$arch" == "x86_64" ]; then
        libFolderName=$sysName\_x86-64
    else
        libFolderName=$sysName\_x86-32
    fi
fi

path=$GRACENOTESDK_ROOT/lib/$libFolderName

echo "Path: $path"
curdir=`pwd`
cd $path/
for file in *.*; do
  echo "Making symlink for $file"
    symlink=${file/\.$version/""}
    ln -s $file $symlink
done

echo Done

if [ "$sysName" == "linux" ]; then
  echo "Copying libs to /usr/local/"
  for file in *.*; do
    echo "Copying $file"
    sudo cp $file /usr/local/lib/
  done
  sudo ldconfig

fi


