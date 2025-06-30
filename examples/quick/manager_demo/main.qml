import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QNdiKit 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 700
    height: 500
    title: "QNdiManager Quick Demo"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // 标题
        Label {
            text: "QNdiManager Quick 演示程序"
            font.pixelSize: 24
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // 说明
        Label {
            text: "这是 NDI Manager 模块的 QML 演示程序\n用于管理和监控 NDI 网络"
            font.pixelSize: 14
            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // 状态显示
        Label {
            id: statusLabel
            text: "状态: 就绪"
            font.pixelSize: 16
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        // 按钮区域
        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            spacing: 15

            Button {
                text: "扫描源"
                onClicked: {
                    ndiManagerItem.scanSources()
                    statusLabel.text = "状态: 扫描源完成"
                }
            }

            Button {
                text: "扫描接收器"
                onClicked: {
                    ndiManagerItem.scanReceivers()
                    statusLabel.text = "状态: 扫描接收器完成"
                }
            }

            Button {
                text: "显示信息"
                onClicked: {
                    ndiManagerItem.showInfo()
                }
            }
        }

        // 结果显示区域
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 20

            // 源列表
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Label {
                    text: "发现的源:"
                    font.bold: true
                }

                ListView {
                    id: sourcesListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: ndiManagerItem ? ndiManagerItem.sources : []
                    delegate: Label {
                        text: modelData
                        padding: 5
                    }
                }
            }

            // 接收器列表
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Label {
                    text: "发现的接收器:"
                    font.bold: true
                }

                ListView {
                    id: receiversListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: ndiManagerItem ? ndiManagerItem.receivers : []
                    delegate: Label {
                        text: modelData
                        padding: 5
                    }
                }
            }
        }

        // NDI Manager Item
        NdiManagerItem {
            id: ndiManagerItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: false  // 隐藏，只用于功能调用
        }

        // 底部信息
        Label {
            text: "点击按钮测试 NDI Manager 功能"
            font.pixelSize: 12
            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }
} 