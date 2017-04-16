#pragma once
#include<QAbstractListModel>
#include "Medicine.h"

#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
	std::vector<Medicine> meds;
public:
	MyListModel(std::vector<Medicine> meds) :meds{ meds } {
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return meds.size();
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto sp = meds[index.row()].getName();
			return QString::fromStdString(sp);
		}
		return QVariant{};
	}
};