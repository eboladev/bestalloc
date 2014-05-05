/*! ---------------------------------------------------------------
 * \file   ConfigReader.cpp
 * \brief  ConfigReader class implementation
 * \author Dmitry Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "ConfigReader.h"
#include "BestAllocException.h"
#include "Constants.h"
using namespace bestalloc;

#include <QMessageBox>
#include <QDebug>

void ConfigReader::save(QString filename, GraphWidget* graphWidget)
{
    if (graphWidget == NULL) return;

    QFile file(filename);
    bool status = file.open(QIODevice::WriteOnly);
    if (status == false) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(ERROR_TITLE);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(SAVE_CONFIG_FILE_ERROR_TEXT);
        msgBox.setInformativeText(WRITE_CONFIG_FILE_ERROR_INFO);
        msgBox.exec();

        file.close();
        return;
    }

    QDataStream stream(&file);

    QList<EmployeeNode*> employees = graphWidget->getEmployeeNodes();
    stream << QVariant::fromValue(employees.size());
    foreach (EmployeeNode* node, employees) {
        stream << QVariant::fromValue(node->getId());
        stream << QVariant::fromValue(QString::fromStdString(node->getName()));
        stream << QVariant::fromValue(node->getNodePicture());
        stream << QVariant::fromValue(node->pos());
    }

    QList<SkillNode*> skills = graphWidget->getSkillNodes();
    stream << QVariant::fromValue(skills.size());
    foreach (SkillNode* node, skills) {
        stream << QVariant::fromValue(node->getId());
        stream << QVariant::fromValue(QString::fromStdString(node->getName()));
        stream << QVariant::fromValue(node->getNodePicture());
        stream << QVariant::fromValue(node->pos());
    }

    QList<GraphEdge*> edges = graphWidget->getEdges();
    stream << QVariant::fromValue(edges.size());
    foreach (GraphEdge* edge, edges) {
        stream << QVariant::fromValue(edge->getWeight());
        stream << QVariant::fromValue(edge->getSourceNode()->getId());
        stream << QVariant::fromValue(edge->getDestNode()->getId());
    }

    file.close();
}

void ConfigReader::load(QString filename, GraphWidget* graphWidget)
{
    if (graphWidget == NULL) return;

    QFile file(filename);
    bool status = file.open(QIODevice::ReadOnly);
    if (status == false) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(ERROR_TITLE);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(LOAD_CONFIG_FILE_ERROR_TEXT);
        msgBox.setInformativeText(READ_CONFIG_FILE_ERROR_INFO);
        msgBox.exec();

        file.close();
        return;
    }

    QDataStream stream(&file);

    QList<EmployeeNode*> employees;
    QList<SkillNode*> skills;
    QList<GraphEdge*> edges;

    try {
        QVariant object;
        stream >> object;
        if (object.canConvert<int>()) {
            int employeesCount = object.value<int>();
            for (int i = 0; i < employeesCount; i++) {
                int nodeId;
                stream >> object;
                if (object.canConvert<int>()) {
                    nodeId = object.value<int>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                QString nodeName;
                stream >> object;
                if (object.canConvert<QString>()) {
                    nodeName = object.value<QString>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }


                QPixmap nodeImage;
                stream >> object;
                if (object.canConvert<QPixmap>()) {
                    nodeImage = object.value<QPixmap>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                QPointF nodePosition;
                stream >> object;
                if (object.canConvert<QPointF>()) {
                    nodePosition = object.value<QPointF>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                EmployeeNode* node = new EmployeeNode(nodeName, nodeImage, graphWidget);
                node->setId(nodeId);
                node->setPos(nodePosition);

                employees.push_back(node);
            }
        } else {
            throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
        }

        stream >> object;
        if (object.canConvert<int>()) {
            int skillsCount = object.value<int>();
            for (int i = 0; i < skillsCount; i++) {
                int nodeId;
                stream >> object;
                if (object.canConvert<int>()) {
                    nodeId = object.value<int>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                QString nodeName;
                stream >> object;
                if (object.canConvert<QString>()) {
                    nodeName = object.value<QString>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }


                QPixmap nodeImage;
                stream >> object;
                if (object.canConvert<QPixmap>()) {
                    nodeImage = object.value<QPixmap>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                QPointF nodePosition;
                stream >> object;
                if (object.canConvert<QPointF>()) {
                    nodePosition = object.value<QPointF>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                SkillNode* node = new SkillNode(nodeName, nodeImage, graphWidget);
                node->setId(nodeId);
                node->setPos(nodePosition);

                skills.push_back(node);
            }
        } else {
            throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
        }

        stream >> object;
        if (object.canConvert<int>()) {
            int edgesCount = object.value<int>();
            for (int i = 0; i < edgesCount; i++) {
                int edgeWeight;
                stream >> object;
                if (object.canConvert<int>()) {
                    edgeWeight = object.value<int>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                int srcNodeId;
                stream >> object;
                if (object.canConvert<int>()) {
                    srcNodeId = object.value<int>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                int destNodeId;
                stream >> object;
                if (object.canConvert<int>()) {
                    destNodeId = object.value<int>();
                } else {
                    throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
                }

                EmployeeNode* srcNode = NULL;
                SkillNode* destNode = NULL;

                foreach (EmployeeNode* node, employees) {
                    if (node->getId() == srcNodeId) {
                        srcNode = node;
                    }
                }

                foreach (SkillNode* node, skills) {
                    if (node->getId() == destNodeId) {
                        destNode = node;
                    }
                }

                if (srcNode != NULL && destNode != NULL) {
                    GraphEdge* edge = new GraphEdge(srcNode, destNode, edgeWeight);
                    edges.push_back(edge);
                }
            }
        } else {
            throw BestAllocException(1, LOAD_CONFIG_FILE_ERROR_INFO);
        }

        graphWidget->setContainers(employees, skills, edges);

    } catch (BestAllocException exp) {
        employees.clear();
        skills.clear();
        edges.clear();

        QMessageBox msgBox;
        msgBox.setWindowTitle(ERROR_TITLE);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(LOAD_CONFIG_FILE_ERROR_TEXT);
        msgBox.setInformativeText(exp.getDescription());
        msgBox.exec();
    }

    file.close();
}
