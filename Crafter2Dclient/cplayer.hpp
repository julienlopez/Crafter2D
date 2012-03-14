#ifndef CPLAYER_HPP
#define CPLAYER_HPP

#include "cworldelement.hpp"

#include <gPlayer>

class QGraphicsSimpleTextItem;

/**
  * \brief Spécialisation de la class gPlayer pour le client.
  *
  *
  */
class cPlayer : public QObject, public cWorldElement, public gPlayer
{
    Q_OBJECT
public:
    cPlayer(quint64 id, QGraphicsItem *parent);
    cPlayer(gPlayer* player);

    void setPosition(const Position& p);
    virtual Position position() const;

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void showMenu();

private:
    QGraphicsSimpleTextItem* m_label;

    void init();

signals:
    void modified();
};

#endif // CPLAYER_HPP
