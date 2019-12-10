#include "logger.h"

Logger *Logger::instance = nullptr;

Logger::Logger(QObject *parent, QString fileName, QPlainTextEdit *editor)
    : QObject(parent)
{
    m_editor = editor;
    m_showDate = true;

    if (!fileName.isEmpty())
    {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value)
{
    QString text = value + "\r\n";

    if (m_showDate)
        text = QDateTime::currentDateTime().toString("DD.MM.YYYY hh:mm:ss ") + text;

    QTextStream out(file);
    out.setCodec("UTF-8");

    if (file != 0)
        out << text;
    if (m_editor != 0)
        m_editor->appendPlainText(text);
}

void Logger::setShowDateTime(bool value)
{
    m_showDate = value;
}

void Logger::initLogger(QObject *parent, QPlainTextEdit *editor)
{
    QString fileName = "discharge.log";
    instance = new Logger(parent, fileName, editor);
}

Logger::~Logger()
{
    if (file != 0)
    file->close();
}
