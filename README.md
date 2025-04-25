# Tic-Tac-Toe Oyunu

Bu proje, minimax algoritması kullanılarak geliştirilmiş bir Tic-Tac-Toe (XOX) oyunudur. Oyun, kullanıcının bilgisayara karşı oynayabileceği şekilde tasarlanmıştır ve üç farklı zorluk seviyesi içermektedir.

## Özellikler

- Üç farklı zorluk seviyesi:
  - Kolay: Bilgisayar %50 ihtimalle en iyi hamleyi, %50 ihtimalle rastgele hamle yapar
  - Orta: Bilgisayar %75 ihtimalle en iyi hamleyi, %25 ihtimalle rastgele hamle yapar
  - Zor: Bilgisayar her zaman en iyi hamleyi yapar
- Minimax algoritması ile optimal oyun stratejisi
- Alpha-beta pruning ile optimizasyon
- Kullanıcı dostu arayüz

## Derleme ve Çalıştırma

```bash
g++ main.cpp -o tictactoe
./tictactoe
```

## Oyun Kuralları

1. Oyun 3x3'lük bir tahta üzerinde oynanır
2. Oyuncu 'X', bilgisayar 'O' sembolünü kullanır
3. Hamleler satır ve sütun numaraları (0-2 arası) girilerek yapılır
4. Üç sembolü yatay, dikey veya çapraz olarak sıralayan ilk oyuncu kazanır
5. Tüm kareler dolduğunda ve kazanan olmadığında oyun berabere biter

## Graph Theory ile İlişkisi

Bu proje, Graph Theory dersi kapsamında şu konularla ilişkilendirilebilir:

1. **Oyun Ağacı (Game Tree)**: 
   - Tic-tac-toe oyunu, olası tüm hamleleri içeren bir oyun ağacı olarak modellenebilir
   - Her düğüm bir oyun durumunu, her kenar bir hamleyi temsil eder
   - Minimax algoritması bu ağaç üzerinde çalışır

2. **Minimax Algoritması**:
   - Oyun ağacında en iyi hamleyi bulmak için kullanılan bir algoritma
   - Maksimum ve minimum değerleri hesaplayarak optimal stratejiyi belirler
   - Alpha-beta pruning ile ağaç üzerinde gereksiz aramaları önler

3. **Oyun Teorisi**:
   - Sıfır toplamlı oyunlar
   - Nash dengesi
   - Optimal strateji belirleme

4. **Karmaşıklık Analizi**:
   - Oyun ağacının boyutu ve derinliği
   - Minimax algoritmasının zaman karmaşıklığı
   - Alpha-beta pruning ile sağlanan optimizasyon

## Rapor İçin Öneriler

1. Oyun ağacının görselleştirilmesi
2. Minimax algoritmasının adım adım çalışma prensibinin açıklanması
3. Farklı zorluk seviyelerinin oyun ağacı üzerindeki etkilerinin analizi
4. Alpha-beta pruning'un sağladığı optimizasyonun nicel analizi
5. Oyunun Nash dengesi açısından değerlendirilmesi
6. Farklı oyun durumlarının grafik teorisi açısından analizi 