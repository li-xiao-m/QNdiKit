import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QNdiKit 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 400
    title: "QNdiSource Quick Demo"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // 标题
        Label {
            text: "QNdiSource Quick 演示程序"
            font.pixelSize: 24
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // 说明
        Label {
            text: "这是 NDI Source 模块的 QML 演示程序\n用于创建和管理 NDI 视频源"
            font.pixelSize: 14
            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // 状态显示
        Label {
            id: statusLabel
            text: "状态: 未启动"
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
                text: "启动 Source"
                onClicked: {
                    ndiSourceItem.startSource()
                    statusLabel.text = "状态: 运行中"
                }
            }

            Button {
                text: "停止 Source"
                onClicked: {
                    ndiSourceItem.stopSource()
                    statusLabel.text = "状态: 已停止"
                }
            }

            Button {
                text: "显示信息"
                onClicked: {
                    ndiSourceItem.showInfo()
                }
            }
        }

        // NDI Source Item
        NdiSourceItem {
            id: ndiSourceItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: false  // 隐藏，只用于功能调用
        }

        // 底部信息
        Label {
            text: "点击按钮测试 NDI Source 功能"
            font.pixelSize: 12
            color: "gray"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }
} 