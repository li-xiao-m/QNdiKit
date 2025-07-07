import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QNK.Manager 1.0

ApplicationWindow {
    id: window

    color: "#121212"
    title: "QNdiManager Quick Demo"
    visible: true
    width: 1070
    height: 710

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 300

            ColumnLayout {
                anchors.fill: parent
                Text {
                    text: "NDI 源列表"
                    font.pixelSize: 24
                    color: "white"
                    Layout.alignment: Qt.AlignCenter
                    Layout.topMargin: 10
                    Layout.bottomMargin: 10
                }

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    border.color: "#222222"
                    border.width: 1
                    color: "#00000000"

                    ListView {
                        id: list_view
                        clip: true
                        anchors.fill: parent
                        anchors.margins: 1
                        model: ndiSourceInfoCtrl.model

                        delegate: Rectangle {
                            color: list_view.currentIndex === index ? "#060606" : mouse_area.containsMouse ? "#060606" : "#121212"
                            height: 40
                            radius: 4
                            width: ListView.view.width

                            MouseArea {
                                id: mouse_area

                                anchors.fill: parent
                                hoverEnabled: true

                                onClicked: {
                                    list_view.currentIndex = index;
                                }
                            }
                            RowLayout {
                                anchors.fill: parent

                                Item {
                                    Layout.fillHeight: true
                                    Layout.preferredWidth: 40
                                }
                                Text {
                                    color: "white"
                                    text: model.source_name
                                }
                                Item {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 276

                    Flow {
                        anchors.fill: parent
                        spacing: 10
                        Button {
                            text: "确定"
                            onClicked: {
                                ndiGlobalCtrl.sendCommand(QNkManagerCore.SwitchNdiSource, ndiSourceInfoCtrl.getNdiSourceInfo(list_view.currentIndex));
                            }
                        }
                        
                    }
                }
            }
        }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            GridLayout {
                anchors.fill: parent
                columns: 2
                rows: 2
                NdiViewerItem {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                NdiViewerItem {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                NdiViewerItem {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                NdiViewerItem {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }
}
