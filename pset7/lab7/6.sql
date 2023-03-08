SELECT name FROM songs WHERE artist_id IN(SELECT id FROM artists WHERE name = "Post Malone");
--SELECT songs.name FROM songs JOIN artists ON artist_id = artists.id WHERE artists.name = "Post Malone";