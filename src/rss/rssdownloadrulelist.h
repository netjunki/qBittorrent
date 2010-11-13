/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2010  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef RSSDOWNLOADRULELIST_H
#define RSSDOWNLOADRULELIST_H

#include <QList>
#include <QHash>
#include <QVariantHash>

#include "rssdownloadrule.h"

// This class is not thread-safe (not required)
class RssDownloadRuleList
{
  Q_DISABLE_COPY(RssDownloadRuleList)

private:
  explicit RssDownloadRuleList();
  static RssDownloadRuleList* m_instance;

public:
  static RssDownloadRuleList* instance();
  static void drop();
  RssDownloadRule findMatchingRule(const QString &feed_url, const QString &article_title) const;
  // Operators
  void saveRule(const RssDownloadRule &rule);
  void removeRule(const QString &name);
  void updateRule(const RssDownloadRule &rule);
  void renameRule(const QString &old_name, const QString &new_name);
  RssDownloadRule getRule(const QString &name) const;
  inline QStringList ruleNames() const { return m_rules.keys(); }

private:
  void loadRulesFromStorage();
  void importRulesInOldFormat(const QHash<QString, QVariant> &rules); // Before v2.5.0
  void loadRulesFromVariantHash(const QVariantHash& l);
  QVariantHash toVariantHash() const;
  void saveRulesToStorage();
  inline QStringList feedRules(const QString &feed_url) const { return m_feedRules[feed_url]; }

private:
  QHash<QString, RssDownloadRule> m_rules;
  QHash<QString, QStringList> m_feedRules;

};

#endif // RSSDOWNLOADFILTERLIST_H
