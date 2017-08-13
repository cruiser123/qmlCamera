import QtQuick 2.8
import QtQuick.Window 2.2
import QtMultimedia 5.9

import CameraFilter 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Rectangle {
        id: rectangle
        color: "red"
        anchors.fill: parent

        Camera {
            objectName: "CameraObject"
            id: camera
            imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
            exposure {
                exposureCompensation: -1.0
                exposureMode: Camera.ExposurePortrait
            }
            captureMode: Camera.CaptureVideo
            flash.mode: Camera.FlashRedEyeReduction
        }

        VideoOutput {
            id: video_output
            objectName: "VidelOutputObject"
            source: camera
            anchors.fill: parent
            focus : visible // to receive focus and capture key events when visible
            autoOrientation: true
            filters: [filter]
            fillMode: VideoOutput.PreserveAspectFit
        }

        CameraFilter {
            objectName: "cameraFilterObject"
            id: filter
            onCameraImage: {
                //                    preview.source = image
            }
            onCameraResolution: {
                var res = "resolution:(%1, %2)"
                text.text = res.arg(resolution.width).arg(resolution.height)
            }
        }
    }

    Row{
        anchors{
            top: parent.top
            left:parent.left
            margins: 8
        }

        Rectangle{
            width: 300
            height: 200
            color: "yellow"
            Image{
                id: preview
            }
        }

        Text{
            id: text
            color: "white"
        }
    }
}

