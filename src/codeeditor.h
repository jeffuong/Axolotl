#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

namespace Ui
{
	class codeEditor;
}

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);

    QString getFilePath();
    QString getFileType();
    void setFilePath(QString newFilePath);
    void setFileType(QString newFileType);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
	int getBCount();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    QString filePath;
    QString fileType;
	int bCount;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor)
    {
        codeEditor = editor;
    }

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H
