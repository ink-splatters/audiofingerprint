#

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

if [ "$arch" == "x86_64" ]; then
    path=$GRACENOTESDK_ROOT/lib/$sysName\_x86-64
  else
    path=$GRACENOTESDK_ROOT/lib/$sysName\_x86-32
fi

if [ "$sysName" == "mac" ]; then
  for file in $path/*.*; do
    echo "Making symlink for $file"
    symlink=${file/\.$version/""}
    ln -s $file $symlink
  done
fi

echo Done

