#pragma once

#ifndef FRAMEHEAD_GADGET_INCLUDED
#define FRAMEHEAD_GADGET_INCLUDED

#include <QEvent>
#include <QObject>

class QPainter;
class FilmstripFrames;
class QEvent;
class QColor;
class QWidget;

class FrameHeadGadget : public QObject
{
	Q_OBJECT

public:
	enum Action { None,
				  MoveHead,
				  ActivateFos,
				  DeactivateFos,
				  ActivateMos,
				  DeactivateMos };

protected:
	bool m_dragging;
	int m_action;
	int m_highlightedFosFrame;
	int m_buttonPressCellIndex;

	int m_highlightedMosFrame;

public:
	FrameHeadGadget();
	virtual ~FrameHeadGadget();

	void draw(QPainter &p, const QColor &lightColor, const QColor &darkColor);

	void drawPlayingHead(QPainter &p, const QColor &lightColor, const QColor &darkColor);
	//reimpremented in FilmstripFrameHeadGadget
	virtual void drawOnionSkinSelection(QPainter &p, const QColor &lightColor, const QColor &darkColor);

	virtual int getY() const = 0;

	virtual int index2y(int index) const = 0;
	virtual int y2index(int y) const = 0;

	virtual void setCurrentFrame(int index) const = 0;
	virtual int getCurrentFrame() const = 0;

	bool isFos(int frame) const;
	bool isMos(int frame) const;
	void setFos(int frame, bool on);
	void setMos(int frame, bool on);

	//reimpremented in FilmstripFrameHeadGadget
	virtual bool eventFilter(QObject *obj, QEvent *event);
};

class XsheetFrameHeadGadget : public FrameHeadGadget
{
public:
};

class FilmstripFrameHeadGadget : public FrameHeadGadget
{
	FilmstripFrames *m_filmstrip;
	int m_dy;

public:
	FilmstripFrameHeadGadget(FilmstripFrames *filmstrip);

	int getY() const;
	int index2y(int index) const;
	int y2index(int y) const;

	void drawOnionSkinSelection(QPainter &p, const QColor &lightColor, const QColor &darkColor);

	void setCurrentFrame(int index) const;
	int getCurrentFrame() const;

	bool eventFilter(QObject *obj, QEvent *event);
};

#endif
