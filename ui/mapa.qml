import QtQuick
import QtQuick
import QtLocation
import QtPositioning

Item {
    visible: true
    width: 800
    height: 600

    function desenharRota(caminhoCoords) {
            console.log("Recebi coordenadas: " + caminhoCoords.length);

            // acessa pelo id
            routeLine.path = caminhoCoords;

            if (caminhoCoords.length > 0) {
                map.center = caminhoCoords[0];
            }
        }

    Plugin {
        id: mapPlugin
        name: "osm" // OpenStreetMap
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(-31.7654, -52.3376)
        zoomLevel: 14

        // linha
        MapPolyline {
            id: routeLine
            line.width: 5
            line.color: "blue"
        }

        // desenha a rota
        function desenharRota(caminhoCoords) {
            routeLine.path = caminhoCoords;

            // centraliza o mapa na rota
            if (caminhoCoords.length > 0) {
                map.center = caminhoCoords[0];
            }
        }

        //  limpa
        function limparRota() {
            routeLine.path = []
        }
    }
}
