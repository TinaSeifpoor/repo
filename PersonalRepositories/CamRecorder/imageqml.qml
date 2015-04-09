import QtQuick 2.0

Image {
    width: 100
    height: 62
    fillMode: Image.PreserveAspectFit
    id: myImage
    source: "image://providerIdPassedToAddImageProvider/foobar"
    cache: false
    function reload() {
        var oldSource = source;
        source = "";
        source = oldSource;
    }
}
