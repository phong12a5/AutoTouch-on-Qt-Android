#include "Model.h"
#include <QWidgetList>
#include <QtWidgets/qwidget.h>
#include <QWindow>

Model* Model::m_instance = nullptr;

Model *Model::instance()
{
    if(m_instance == nullptr){
        m_instance = new Model();
    }
    return m_instance;
}

void Model::testFunc(int caseIndex, QString extraData)
{
    LOG << "caseIndex: " << caseIndex << " --- ExtraData: " << extraData;
    emit requestTestCase(caseIndex);
}

int Model::widthDisplay() const
{
    return m_widthDisplay;
}

void Model::setWidthDisplay(const int width)
{
    LOG << "width: " << width;
    if(width != m_widthDisplay){
        m_widthDisplay = width;
        emit widthDisplayChanged();
    }
}

int Model::heightDisplay() const
{
    return m_heightDisplay;
}

void Model::setHeightDisplay(const int height)
{
    LOG << "height: " << height;
    if(height != m_heightDisplay){
        m_heightDisplay = height;
        emit heightDisplayChanged();
    }
}

Model::Model(QObject *parent) : QObject(parent)
{
    m_widthDisplay = 0;
    m_heightDisplay = 0;
}

