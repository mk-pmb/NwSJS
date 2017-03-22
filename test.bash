for f in node_modules/typescript/lib/*.js
do
    printf "Compressing $f\n"
    time ./nwsjs $f --comments --spaces --tabs > tmp
    mv tmp $f
done

for f in *.ts
do
    ./node_modules/.bin/tsc $f
    if [ $? != 0 ]; then
        exit 1
    fi
    artifact=$(echo $f | awk '{gsub("\\.ts",".js");print}')

    ./node_modules/.bin/browserify $artifact --node --debug -o bundle$artifact
    if [ $? != 0 ]; then
        exit 1
    fi
    printf "Compressing Browserify bundle\n"
    time ./nwsjs bundle$artifact --comments --spaces --tabs > compBundle$artifact
    if [ $? != 0 ]; then
        exit 1
    fi

    node bundle$artifact
    retValBundle=$?

    node compBundle$artifact
    if [ $? != "$retValBundle" ]; then
        exit 1
    fi

done
